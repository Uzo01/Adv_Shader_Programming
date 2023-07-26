#version 330 core 
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;
vec3 getNorm();

in vec2 TexCoordsES[];
in vec3 posES[];
in vec3 normES[];

out vec3 gNormals;
out vec3 gWorldPos_FS_in;
out vec2 TexCoordsGS;
out vec3 tessNorm;
out mat3 gTBN;

vec3 getNormal();
vec3 pos;
vec3 normal;
vec3 posX;
vec3 posY;
vec3 uvX;
vec3 uvY;
vec3 tan;
vec3 biTan;
mat3 TBN;

void main()
{
	for (int i = 0 ; i < 3; i++)
	{
		gl_Position = gl_in[i].gl_Position;
		gWorldPos_FS_in = posES[i];
		tessNorm = normES[i];
		gNormals = getNormal();
		TexCoordsGS = TexCoordsES[i];



		EmitVertex();
	}
	EndPrimitive();
}

vec3 getNormal()
{
	vec3 a = vec3(gl_in[1].gl_Position) - vec3(gl_in[0].gl_Position);
	vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[0].gl_Position);
	return normalize(cross(b, a));
}

