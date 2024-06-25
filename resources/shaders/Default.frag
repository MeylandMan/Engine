#version 410 core

out vec4 fragColor;
out vec4 in_Color;

in vec2 v_TexCoords;
in vec4 v_Colors;

uniform sampler2D u_Texture;

void main() {
	 
	fragColor = v_Colors * texture(u_Texture, v_TexCoords);

	//FragColor = vec4(v_TexCoords, 0.0, 1.0); /*(Showing the Texture mapping)*/
}
