#version 410 core
out vec4 frag_color;
uniform vec4 incolor;
uniform vec3 mouse;
uniform vec2 screen_res;

void main() {
    frag_color = incolor;
    if (gl_FragCoord.x > mouse.x)
        frag_color = vec4(1.0, 0.0, 0.0, 1.0);
    else
        frag_color = vec4(0.0, 1.0, 0.0, 1.0);
    frag_color.y = sin(mouse.y / 1000);
    if (mouse.z > 0)
        frag_color.r = mouse.z;
}
