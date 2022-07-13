#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float Val1offset;
uniform float Val2offset;

void main()
{
	//FragColor = vec4(ourColor,1.0);
	if(Val1offset == 1.0){
		FragColor = mix(texture(texture1, TexCoord) , vec4(ourColor, 0.1) , Val2offset);
	} else {
		FragColor = mix(texture(texture2, TexCoord) , vec4(ourColor, 0.1) , Val2offset);
	}

}