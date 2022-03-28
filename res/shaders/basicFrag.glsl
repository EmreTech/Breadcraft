#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord);//vec4(1.0f, 0.5f, 0.2f, 1.0f);

    if (FragColor.a < 0.1f)
    {
        discard;
    }
} 