#version 410 core
layout(location = 0) in vec2 verts;
layout(location = 1) in vec3 transform;
// attribute vec4 in gl_Vertex;
uniform float u_time;
mat2 rotate2d(float angle){
    return mat2(cos(angle), -sin(angle),
                sin(angle),  cos(angle));
}
void main() {
    gl_Position.xy = verts.xy;
    // gl_Position.xy = verts.xy * rotate2d(u_time / 3600);
    // gl_Position.xy = verts.xy * rotate2d(u_time / 3600);
    // gl_Position.xy = verts.xy * vec2(1, 1);
    // gl_Position.xy = verts.xy * vec2(0.5, 0.5);
    // gl_Position.x = verts.x + u_time / 1000;
    // debugPrintfEXT("The value of my float is %f", u_time);
    gl_Position.z = 0;
    gl_Position.w = 1;
    // gl_Position.w = 0.2;
}
