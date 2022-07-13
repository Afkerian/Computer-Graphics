#version 330 core
out vec4 FragColor;

in vec3 ourColor;
uniform vec4 timeColor;
void main()
{
    // timeColor modifica los colores previamente establecidos en el arreglo de vertices (ourColor).
    FragColor = vec4(ourColor.x-timeColor.x, ourColor.y-timeColor.y, ourColor.z-timeColor.z, 1.0f);
}