#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform vec2 texelSize;

void main() {
  FragColor = texture(texture1, TexCoord);
}