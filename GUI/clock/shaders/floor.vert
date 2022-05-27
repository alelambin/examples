#version 330 core

attribute vec3 aPosition;

varying vec3 vPosition;
varying vec2 vTexturePosition;
varying vec4 vLightPosition;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform mat4 uLightView;
uniform mat4 uLightProjection;

void main() {
    vPosition = vec3(uModel * vec4(aPosition, 1.0));
    vTexturePosition = 0.2 * aPosition.xz;
    vLightPosition = uLightProjection * uLightView * uModel * vec4(aPosition, 1.0);
    gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);
}
