#version 410 core
out vec4 frag_color;
uniform vec4 incolor;
uniform vec3 mouse;
uniform vec2 screen_res;

void main() {
    frag_color = incolor;
    frag_color.xy = sin(mouse.xy / 1000);
    frag_color.r = mouse.z;
}
