#version 110

// Vertex structure
// Set order of vertex structure (position, color)
// Search in C++ code funciton GL20Mesh::Render()
// glVertexAttribPointer(0, ...) // this is "position"
// glVertexAttribPointer(1, ...) // this is "color"
attribute vec3 position;
attribute vec4 color;

// Shader parameters
// Search in C++ code functions like "glUniform4"
// i.e. functions: glUniform4fv(), glUniformMatrix4fv().
// These functions pass to shader parameters listed below
uniform vec4 constColor;
uniform vec4 time;
uniform mat4 matrixWorldViewProjT;

void main()
{
	//gl_Position = matrixWorldViewProjT * vec4(position, 1.0);	// OpenGL
	
	
	float len = 1.0 - length(position);
	vec3 pos = position/(1.0 - len*abs(time.x));
		
	gl_Position = vec4(pos, 1.0) * matrixWorldViewProjT;	// DirectX
	gl_FrontColor = color * constColor;
}