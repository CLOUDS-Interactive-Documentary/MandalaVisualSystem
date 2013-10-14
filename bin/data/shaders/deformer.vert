#version 120
#extension GL_ARB_texture_rectangle : enable

uniform float time;
uniform float radius = 10.;

varying vec3 norm;
varying vec3 ePos;
varying vec2 uv;

varying float isSide;

float PI = 3.14159265359;
float TWO_PI = 6.28318530718;
float epsilon = 0.0000001f;

vec3 mandala( float phi, float theta, float radius )
{
	return vec3( cos( phi ) * sin(theta), cos( theta ), sin( phi ) * sin( theta ) ) * radius;
}


void main()
{
	float xPos = gl_Vertex.x;
	float yPos = gl_Vertex.y + sin(time)*.25;
	float zPos = gl_Vertex.z;
	
	vec3 vertex;
	norm = gl_Normal;
	
	float rad = radius + zPos;
	vertex = mandala( xPos, yPos, rad );
	
	if( abs(norm.x) > .5 || abs(norm.y) > .5)
	{
		norm = gl_NormalMatrix * ( mandala( xPos+norm.x, yPos+norm.y, rad ) - vertex );
		isSide = 1.;
	}
	else
	{
		norm = gl_NormalMatrix * vertex * norm.z/abs(norm.z);
		isSide = 0.;
	}
	
	vec4 ecPosition = gl_ModelViewMatrix * vec4( vertex, 1. );
	ePos = normalize(ecPosition.xyz/ecPosition.w);
	gl_Position = gl_ProjectionMatrix * ecPosition;
	
	uv = gl_MultiTexCoord0.xy;
}

