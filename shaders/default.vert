#version 410 core
in vec3 vp;
layout(location = 2) in vec2 mouse_vert;
void main() {
    gl_Position.xyz = vp;
    gl_Position.x += 0.4;
    //gl_Position.xy = mouse_vert / 1000;
    gl_Position.w = 1.0;
}
