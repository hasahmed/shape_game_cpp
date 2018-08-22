#version 410 core
out vec4 frag_color;
uniform vec4 incolor;
uniform vec2 mouse;

void main() {
    frag_color = incolor;
    frag_color.xy = sin(mouse.xy / 1000);
}
