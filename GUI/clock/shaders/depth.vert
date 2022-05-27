#version 330 core

attribute vec3 aPosition;

varying vec4 vPosition;

uniform mat4 uLightModel;
uniform mat4 uLightView;
uniform mat4 uLightProjection;

void main() {
    vPosition = uLightProjection * uLightView * uLightModel * vec4(aPosition, 1.0);
    gl_Position = vPosition;
}
