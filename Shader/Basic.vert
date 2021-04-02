#version 330

in vec3 inPosition;

void main()
{
	// TODO:ここにシェーダーコードを書く
	gl_Position=vec4(inPosition,1.0);
}
