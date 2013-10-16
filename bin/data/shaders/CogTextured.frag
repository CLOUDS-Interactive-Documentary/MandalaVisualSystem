
#version 120
#extension GL_ARB_texture_rectangle : enable


uniform sampler2DRect frontTexture;
uniform int usingFrontTexture = 0;
uniform vec2 frontTexDim;

uniform sampler2DRect sideTexture;
uniform int usingSideTexture = 0;
uniform vec2 sideTexDim;

uniform float specularScale = 1.;
uniform float specularExpo = 32.;

uniform vec2 sweep;
uniform vec2 startSweep;

uniform vec3 sideColor = vec3( 1., .6, .1);
uniform float discardThreshold = .005;

varying vec3 norm;
varying vec3 ePos;
varying vec2 uv;
varying float isSide;
varying float phi;
varying float theta;


float PI = 3.14159265359;
float TWO_PI = 6.28318530718;
float epsilon = 0.0000001f;

void main(void)
{
	vec3 normal = normalize( norm );
	float fr = dot( -normalize(ePos), normal ) ;
	fr *= specularScale * pow( fr* .5 + .5, specularExpo);
	
	gl_FragColor = vec4( vec3(fr), 1.);
	
	
	if(isSide > .9)
	{
		if(usingSideTexture > .9)
		{
			gl_FragColor += texture2DRect( sideTexture, uv * sideTexDim );
		}
	}
	else
	{
		if(usingFrontTexture > .9)
		{
			gl_FragColor += texture2DRect( frontTexture, uv * frontTexDim );
		}
	}
	
	//
	if(gl_FragColor.w < discardThreshold)	discard;
}

