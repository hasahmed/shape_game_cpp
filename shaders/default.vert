#version 410 core
layout(location = 0) in vec3 verts;
layout(location = 1) in vec3 transform;
uniform float u_time;
void main() {
    // gl_Position.xyz = verts * vec3(2, 2, 0);
    // gl_Position.xy = verts.xy * vec2(1, 1);
    gl_Position.xy = verts.xy * vec2(0.5, 0.5);
    // gl_Position.x = verts.x + u_time / 1000;
    // debugPrintfEXT("The value of my float is %f", u_time);
    gl_Position.z = 1.0;
    gl_Position.w = 1.0;
}
