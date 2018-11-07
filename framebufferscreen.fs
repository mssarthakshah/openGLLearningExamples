#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
//uniform vec4 prevFrameBufferData;
uniform sampler2D screenTexture;

uniform sampler2D prevFrameBufDataAsTex;

precision mediump float;
vec4 Blend(vec4 src, vec4 dst){

vec4 result;
result.a = src.a + dst.a * (1.0-src.a);
result.rgb = src.rgb  + dst.rgb ;    
return result;
}

void main()
{
	vec3 prevcol = texture(prevFrameBufDataAsTex, TexCoords).rgb;

	vec3 col = texture(screenTexture, TexCoords).rgb;
    //FragColor =   vec4(prevcol,1.0) * vec4(col,1.0);
	FragColor = Blend(vec4(prevcol, 0.25), vec4(col , 0.75));
} 

