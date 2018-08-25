#version 410 core
out vec4 frag_color;
uniform vec4 incolor;
uniform vec3 mouse;
uniform vec2 screen_res;
uniform float u_time;

void main() {
    frag_color = incolor;
    frag_color.r = abs(sin(u_time));
    frag_color.r = abs(sin(u_time));
    if (gl_FragCoord.x > mouse.x)
        frag_color.y = mouse.x / 1000;
    else
        frag_color.b = mouse.x / 1000;
    //frag_color.y = sin(mouse.y / 1000);
    //if (mouse.z > 0)
        //frag_color.r = sin(u_time);
}
