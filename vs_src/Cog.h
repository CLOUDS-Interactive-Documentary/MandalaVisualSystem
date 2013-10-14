//
//  Cog.h
//  MandalaVisualSystem
//
//  Created by laserstorm on 10/12/13.
//
//

#include "ofMain.h"

class Cog : public ofNode{
public:
	Cog(float _radius,
		float _thickness,
		float _startU,
		float _sweepU,
		float _startV,
		float _sweepV)
	{
		m = NULL;
		shader != NULL;
		bDrawWireframe = false;
		
		setup( _radius, _thickness, _startU, _sweepU, _startV, _sweepV);
	};
	
	Cog()
	{
		m = NULL;
		shader != NULL;
		bDrawWireframe = false;
		
		setup( 10, 2, 0, .5, 0.25, .75);
	};
	
	~Cog()
	{
		clearMesh();
	};
	
	void setup(float _radius,
			   float _thickness,
			   float _startU,
			   float _sweepU,
			   float _startV,
			   float _sweepV)
	{
		thickness = _thickness;
		radius = _radius;
		
		subdScl = 10;
		
		//get our subd for u and v
		minU = TWO_PI * _startU;
		maxU = TWO_PI * (_startU + _sweepU);
		minV = PI * _startV;
		maxV = PI * (_startV + _sweepV);
		
		sweepU = maxU - minU;
		sweepV = maxV - minV;
		
		subdU = radiansToSdubd( sweepU );
		subdV = radiansToSdubd( sweepV );
		
		setupMesh();
	}
	
	void draw( ofShader* _shader = NULL )
	{
		if(_shader == NULL)	_shader = shader;
		
		if(_shader != NULL && m != NULL)
		{
			ofPushMatrix();
//			ofMultMatrix( getGlobalTransformMatrix() );
			
			_shader->begin();
			_shader->setUniform1f( "time", ofGetElapsedTimef() );
			_shader->setUniform1f( "radius", radius );
			
			bDrawWireframe ? m->drawWireframe() : m->draw();
			
			_shader->end();
			ofPopMatrix();
		}
	}
	
	void drawBorders()
	{
		//just draw the side edges
	};
	
	void setupMesh()
	{
		clearMesh();
		
		m = createCog( minU, maxU, minV, maxV, thickness, subdU, subdV );
	}
	
	void clearMesh()
	{
		if(m!=NULL)
		{
			m->clear();
		}
		delete m;
		m = NULL;
	}
	
	void clear(){
		clearMesh();
	}
	
	int radiansToSdubd( float radians )
	{
		//TODO: incorperate radius here
		return int(radians * subdScl);
	}
	
	ofShader* shader;
	
	
	ofVec3f normalFrom3Points(ofVec3f p0, ofVec3f p1, ofVec3f p2)
	{
		return (p2 - p1).cross( p0 - p1).normalized();
	}
	
	ofVboMesh* createCog( float uRadiansMin, float uRadiansMax, float vRadiansMin, float vRadiansMax, float thickness, int subdX, int subdY );
	ofVboMesh* createBoxMesh( float low_w, float hi_w, float low_h, float hi_h, float low_d, float hi_d, int _subx, int _suby, int _subz);
	
	ofVboMesh* m;
	float radius, thickness, minU, maxU, minV, maxV, subdU, subdV, subdScl, sweepU, sweepV;
	bool bDrawWireframe;
	
};