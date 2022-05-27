#version 330 core

varying vec3 vPosition;
varying vec2 vTexturePosition;
varying vec4 vLightPosition;

uniform sampler2D uShadowMap;
uniform sampler2D uTexture;

uniform vec3 uCameraPosition;
uniform vec3 uLightPosition;
uniform vec3 uLightColor;
uniform float uLightInnerCut;
uniform float uLightOuterCut;
uniform int uLightType;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform mat4 uLightView;
uniform mat4 uLightProjection;

float shadowMapCalculation(sampler2D map, vec2 coordinates, float compare) {
    vec4 vector = texture2D(map, coordinates);
    float value = vector.x * 255.0 + (vector.y * 255.0 + (vector.z * 255.0 + vector.w) / 255.0) / 255.0;
    return step(compare, value);
}

float shadowMapLinear(sampler2D map, vec2 coordinates, float compare, vec2 texelSize) {
    vec2 pixelSize = coordinates / texelSize + 0.5;
    vec2 pixelFractPart = fract(pixelSize);
    vec2 startTexel = (pixelSize - pixelFractPart) * texelSize;

    float bottomLeftTexel = shadowMapCalculation(map, startTexel, compare);
    float bottomRightTexel = shadowMapCalculation(map, startTexel + vec2(texelSize.x, 0.0), compare);
    float topLeftTexel = shadowMapCalculation(map, startTexel + vec2(0.0, texelSize.y), compare);
    float topRightTexel = shadowMapCalculation(map, startTexel + texelSize, compare);

    float mixLeft = mix(bottomLeftTexel, topLeftTexel, pixelFractPart.y);
    float mixRight = mix(bottomRightTexel, topRightTexel, pixelFractPart.y);
    return mix(mixLeft, mixRight, pixelFractPart.x);
}

float shadowMapPointCloudFiltering(sampler2D map, vec2 coordinates, float compare, vec2 texelSize) {
    float result = 0.0;
    for (int y = -1; y <= 1; y++)
        for (int x = -1; x <= 1; x++)
            result += shadowMapLinear(map, coordinates + texelSize * vec2(x, y), compare, texelSize);
    return result;
}

float shadowAmount(sampler2D map, vec4 initialShadowCoordinates) {
    vec3 value = (initialShadowCoordinates.xyz / initialShadowCoordinates.w + vec3(1.0)) * 0.5;
    float shadow = shadowMapPointCloudFiltering(map, value.xy, value.z * 255.0 - 0.5, vec2(1.0 / 1024)) * 0.5 + 0.5;
    if (shadow > 1.0)
        shadow = 1.0;
    return shadow;
}

vec4 directionalLight() {
    /* Background component */
    vec3 ambient = uLightColor * texture2D(uTexture, vTexturePosition).rgb;

    /* Scattered component */
    vec3 normal = normalize(vec3(0.0, 1.0, 0.0));
    vec3 lightDirection = normalize(uLightPosition);
    vec3 diffuse = uLightColor * max(dot(normal, lightDirection), 0.0) * texture2D(uTexture, vTexturePosition).rgb;

    /* Reflected component */
    vec3 cameraDirection = normalize(uCameraPosition - vPosition);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    vec3 specular = uLightColor * pow(max(dot(cameraDirection, reflectDirection), 0.0), 12.8) * vec3(0.316228, 0.316228, 0.316228);

    float distance = length(uLightPosition - vPosition);
    float attenuation = 0.5;

    float shadow = shadowAmount(uShadowMap, vLightPosition);

    return vec4(attenuation * (ambient + diffuse + specular), 1.0) * shadow;
}

vec4 pointLight() {
    /* Background component */
    vec3 ambient = uLightColor * texture2D(uTexture, vTexturePosition).rgb;

    /* Scattered component */
    vec3 normal = normalize(vec3(0.0, 1.0, 0.0));
    vec3 lightDirection = normalize(uLightPosition - vPosition);
    vec3 diffuse = uLightColor * max(dot(normal, lightDirection), 0.0) * texture2D(uTexture, vTexturePosition).rgb;

    /* Reflected component */
    vec3 cameraDirection = normalize(uCameraPosition - vPosition);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    vec3 specular = uLightColor * pow(max(dot(cameraDirection, reflectDirection), 0.0), 12.8) * vec3(0.316228, 0.316228, 0.316228);

    float distance = length(uLightPosition - vPosition);
    float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.032 * pow(distance, 2.0));

    float shadow = shadowAmount(uShadowMap, vLightPosition);

    return vec4(attenuation * (ambient + diffuse + specular), 1.0) * shadow;
}

vec4 spotLight() {
    /* Background component */
    vec3 ambient = uLightColor * texture2D(uTexture, vTexturePosition).rgb;

    /* Scattered component */
    vec3 normal = normalize(vec3(0.0, 1.0, 0.0));
    vec3 lightDirection = normalize(uLightPosition - vPosition);
    vec3 diffuse = uLightColor * max(dot(normal, lightDirection), 0.0) * texture2D(uTexture, vTexturePosition).rgb;

    /* Reflected component */
    vec3 cameraDirection = normalize(uCameraPosition - vPosition);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    vec3 specular = uLightColor * pow(max(dot(cameraDirection, reflectDirection), 0.0), 12.8) * vec3(0.316228, 0.316228, 0.316228);

    float angle = dot(lightDirection, normalize(uLightPosition));
    float intensity = clamp((angle - uLightOuterCut) / (uLightInnerCut - uLightOuterCut), 0.0, 1.0);

    float distance = length(uLightPosition - vPosition);
    float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.032 * pow(distance, 2.0));

    float shadow = shadowAmount(uShadowMap, vLightPosition);

    return vec4(attenuation * (ambient + intensity * (diffuse + specular)), 1.0) * shadow;
}

void main() {
    switch (uLightType) {
        case 0:
            gl_FragColor = directionalLight();
            break;
        case 1:
            gl_FragColor = pointLight();
            break;
        case 2:
            gl_FragColor = spotLight();
            break;
        default:
            gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
}
