#version 150

out vec4 outputColor;
uniform float time;
uniform float colourR;
uniform float colourG;
uniform float colourB;
uniform float shaderControl;
uniform vec2 resolution;

void main() {
    vec2 spectacularColours = gl_FragCoord.xy / resolution.xy * 2.0;
    for(float i = 1.0; i < 30.0; i++){
        spectacularColours.x += 0.7 / i * sin(i * 3.0 * spectacularColours.y + time * shaderControl + cos((time / (50. * i)) * i));
        spectacularColours.y += 0.2/ i * cos(i * 3.0 * spectacularColours.x + time * shaderControl + sin((time / (300. * i)) * i));
    }
    float r = cos(spectacularColours.x + spectacularColours.y + colourR) * 0.3;
    float g = sin(spectacularColours.x + spectacularColours.y + colourG) * 0.3;
    float b = (sin(spectacularColours.x + spectacularColours.y + colourB) + cos(spectacularColours.x + spectacularColours.y + 3.0))*0.25 + 0.5;
    outputColor = vec4(r, g, b, 1);
}
