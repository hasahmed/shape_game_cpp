#version 410 core
layout(location = 0) in vec2 verts;
// attribute vec4 in gl_Vertex;
uniform float u_time;
uniform vec2 scale;
uniform vec2 pos;
uniform vec2 origin;
uniform vec2 window_dim;
uniform float rotation; // TODO pass in
mat2 rotate2d(float angle){
    return mat2(cos(angle), -sin(angle),
                sin(angle),  cos(angle));
}
void main() {
    vec2 adj_scale = vec2(2.0 / window_dim.x, 2.0 / window_dim.y);
    // gl_Position.xy = ((verts.xy - origin) * scale + origin) * adj_scale;
    // gl_Position.xy = ((verts.xy - origin) * scale + origin) * adj_scale;
    // vec2 adj_scale = vec2(2.0f / window_dim.x, 2.0f / window_dim.y);
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
