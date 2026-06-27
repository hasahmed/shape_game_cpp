#version 410 core
in vec3 vp;
void main() {
    gl_Position.xyz = vp;
    gl_Position.w = 1.0;
}
