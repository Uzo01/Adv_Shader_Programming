#version 330 core

vec3 getDirectionalLight (vec3 norm, vec3 viewDir);
vec3 getTerrainCol (vec3 col);
out vec4 FragColor ;



in vec3 gNormals;
in vec3 gWorldPos_FS_in;
in vec2 TexCoordsGS;
in vec3 tessNorm;
in float scale;

uniform vec3 ColLight;
uniform vec3 dirLight;
uniform vec3 viewPos;


uniform sampler2D groundTexdDiff;


float ambientFactor = 0.1;
float shine = 70;
float spcStrength = 0.8;


void main()
{
vec3 gNorm = normalize(tessNorm);
vec3 viewDir = normalize(viewPos - gWorldPos_FS_in);

vec3 result = vec3(0.0f);
result = getDirectionalLight(gNorm, viewDir);

vec3 col ;
float height = gWorldPos_FS_in.y;
vec3 green = vec3(0.3,0.35,0.15);
vec3 gray = vec3(0.5,0.4,0.5);
vec3 brown = vec3(0.5,0.35,0.05);
  
if (height > 30)
	col = vec3(mix(green, gray, smoothstep(35, 80,height)).xyz);
else if (height > 5)
	col = vec3(mix(green, brown, smoothstep(25, 100,height)).xyz);
else
	col = green;
  result = col + result;
  result = result ;
   FragColor = vec4 (result, 1.0);
}
//


vec3 getDirectionalLight (vec3 gNorm, vec3 viewDir)
{
vec3 terrainCol = vec3(0.f, 0.f, 1.f);
	// diff texture
vec3 diffMapCol = texture(groundTexdDiff, TexCoordsGS).xyz;
	//Ambient
vec3 ambientColor = ColLight*diffMapCol*ambientFactor;
//Diffuse
  float diffFactor = dot (gNorm, -dirLight); //surface norm and light direcrtion is negated
  diffFactor = max(diffFactor, 0.0);
  vec3 diffCol = ColLight*diffMapCol*diffFactor;
  //Specular
  vec3 reflectDir = reflect(dirLight, gNorm);
  float specFactor = dot(viewDir, reflectDir);
  specFactor = max(specFactor, 0.0);
  specFactor = pow(specFactor, shine);
  vec3 specCol = ColLight*specFactor*spcStrength;

   vec3 result = ambientColor + diffCol + specCol ;
   return result;
}


