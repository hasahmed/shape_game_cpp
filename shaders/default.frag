#version 410 core
out vec4 frag_color;
uniform vec4 incolor;
uniform vec3 mouse;
uniform vec2 screen_res;
uniform float u_time;

void main() {
    // frag_color = incolor;
    frag_color = rgb(1, 0, 0, 1);
}
