//
//  Cog.cpp
//  MandalaVisualSystem
//
//  Created by laserstorm on 10/12/13.
//
//

#include "Cog.h"

ofVboMesh* Cog::createCog( float uRadiansMin, float uRadiansMax, float vRadiansMin, float vRadiansMax, float thickness, int subdX, int subdY )
{
	return createBoxMesh(uRadiansMin, uRadiansMax, vRadiansMin, vRadiansMax, 0, thickness, subdX, subdY, 1 );
}

ofVboMesh* Cog::createBoxMesh( float low_w, float hi_w, float low_h, float hi_h, float low_d, float hi_d, int _subx, int _suby, int _subz )
{
	ofVboMesh* m = new ofVboMesh;
	
	int subx = max( 1, _subx );
	int suby = max( 1, _suby );
	int subz = max( 1, _subz );
	
	
	vector<ofVec3f> v;
	vector<ofVec2f> uv;
	vector<ofIndexType> indices;
	
	float stepX = (hi_w - low_w)/subx;
	float stepY = (hi_h - low_h)/suby;
	float stepZ = (hi_d - low_d)/subz;
	
	float uvStepX = 1./subx;
	float uvStepY = 1./suby;
	float uvStepZ = 1./subz;
	
	vector< vector< int > > tempIndices;
	
	//front
	tempIndices.resize(subx+1);
	for (int i=0; i<tempIndices.size(); i++)
	{
		tempIndices[i].resize(suby+1);
		for (int j=0; j<tempIndices[i].size(); j++)
		{
			tempIndices[i][j] = v.size();
			v.push_back( ofVec3f( i*stepX + low_w, j*stepY + low_h, hi_d ) );
			uv.push_back( ofVec2f(i*uvStepX, j*uvStepY) );
		}
	}
	for (int i = 0; i<tempIndices.size()-1; i++)
	{
		for(int j=0; j<tempIndices[i].size()-1; j++)
		{
			indices.push_back( tempIndices[i][j] );
			indices.push_back( tempIndices[i+1][j+1] );
			indices.push_back( tempIndices[i][j+1] );
			
			indices.push_back( tempIndices[i][j] );
			indices.push_back( tempIndices[i+1][j] );
			indices.push_back( tempIndices[i+1][j+1] );
		}
		tempIndices[i].clear();
	}
	tempIndices.clear();
	
	//back
	tempIndices.resize(subx+1);
	for (int i=0; i<tempIndices.size(); i++)
	{
		tempIndices[i].resize(suby+1);
		for (int j=0; j<tempIndices[i].size(); j++)
		{
			tempIndices[i][j] = v.size();
			v.push_back( ofVec3f( i*stepX + low_w, j*stepY + low_h, low_d ) );
			uv.push_back( ofVec2f(i*uvStepX, j*uvStepY) );
		}
	}
	for (int i = 0; i<tempIndices.size()-1; i++)
	{
		for(int j=0; j<tempIndices[i].size()-1; j++)
		{
			indices.push_back( tempIndices[i][j] );
			indices.push_back( tempIndices[i][j+1] );
			indices.push_back( tempIndices[i+1][j+1] );
			
			indices.push_back( tempIndices[i][j] );
			indices.push_back( tempIndices[i+1][j+1] );
			indices.push_back( tempIndices[i+1][j] );
		}
		tempIndices[i].clear();
	}
	tempIndices.clear();
	
	
	//left
	tempIndices.resize(suby+1);
	for (int i=0; i<tempIndices.size(); i++)
	{
		tempIndices[i].resize(subz+1);
		for (int j=0; j<tempIndices[i].size(); j++)
		{
			tempIndices[i][j] = v.size();
			v.push_back( ofVec3f( hi_w, i*stepY + low_h, j*stepZ + low_d ) );
			uv.push_back( ofVec2f(i*uvStepY, j*uvStepZ) );
		}
	}
	for (int i = 0; i<tempIndices.size()-1; i++)
	{
		for(int j=0; j<tempIndices[i].size()-1; j++)
		{
			indices.push_back( tempIndices[i][j] );
			indices.push_back( tempIndices[i+1][j+1] );
			indices.push_back( tempIndices[i][j+1] );
			
			indices.push_back( tempIndices[i][j] );
			indices.push_back( tempIndices[i+1][j] );
			indices.push_back( tempIndices[i+1][j+1] );
		}
		tempIndices[i].clear();
	}
	tempIndices.clear();
	
	//right
	tempIndices.resize(suby+1);
	for (int i=0; i<tempIndices.size(); i++)
	{
		tempIndices[i].resize(subz+1);
		for (int j=0; j<tempIndices[i].size(); j++)
		{
			tempIndices[i][j] = v.size();
			v.push_back( ofVec3f( low_w, i*stepY + low_h, j*stepZ + low_d ) );
			uv.push_back( ofVec2f(i*uvStepY, j*uvStepZ) );
		}
	}
	for (int i = 0; i<tempIndices.size()-1; i++)
	{
		for(int j=0; j<tempIndices[i].size()-1; j++)
		{
			indices.push_back( tempIndices[i][j] );
			indices.push_back( tempIndices[i][j+1] );
			indices.push_back( tempIndices[i+1][j+1] );
			
			indices.push_back( tempIndices[i][j] );
			indices.push_back( tempIndices[i+1][j+1] );
			indices.push_back( tempIndices[i+1][j] );
		}
		tempIndices[i].clear();
	}
	tempIndices.clear();
	
	//top
	tempIndices.resize(subx+1);
	for (int i=0; i<tempIndices.size(); i++)
	{
		tempIndices[i].resize(subz+1);
		for (int j=0; j<tempIndices[i].size(); j++)
		{
			tempIndices[i][j] = v.size();
			v.push_back( ofVec3f(  i*stepX + low_w, hi_h, j*stepZ + low_d ) );
			uv.push_back( ofVec2f(i*uvStepX, j*uvStepZ) );
		}
	}
	for (int i = 0; i<tempIndices.size()-1; i++)
	{
		for(int j=0; j<tempIndices[i].size()-1; j++)
		{
			indices.push_back( tempIndices[i][j] );
			indices.push_back( tempIndices[i][j+1] );
			indices.push_back( tempIndices[i+1][j+1] );
			
			indices.push_back( tempIndices[i][j] );
			indices.push_back( tempIndices[i+1][j+1] );
			indices.push_back( tempIndices[i+1][j] );
		}
		tempIndices[i].clear();
	}
	tempIndices.clear();
	
	
	//bottom
	tempIndices.resize(subx+1);
	for (int i=0; i<tempIndices.size(); i++)
	{
		tempIndices[i].resize(subz+1);
		for (int j=0; j<tempIndices[i].size(); j++)
		{
			tempIndices[i][j] = v.size();
			v.push_back( ofVec3f(  i*stepX + low_w, low_h, j*stepZ + low_d ) );
			uv.push_back( ofVec2f(i*uvStepX, j*uvStepZ) );
		}
	}
	for (int i = 0; i<tempIndices.size()-1; i++)
	{
		for(int j=0; j<tempIndices[i].size()-1; j++)
		{
			indices.push_back( tempIndices[i][j] );
			indices.push_back( tempIndices[i+1][j+1] );
			indices.push_back( tempIndices[i][j+1] );
			
			indices.push_back( tempIndices[i][j] );
			indices.push_back( tempIndices[i+1][j] );
			indices.push_back( tempIndices[i+1][j+1] );
		}
		tempIndices[i].clear();
	}
	tempIndices.clear();
	
	//compute smoothed normals( one normal per vertex, not per face)
	vector<ofVec3f> n(v.size());
	ofVec3f norm;
	for (int i=0; i<indices.size(); i+=3)
	{
		norm = normalFrom3Points( v[indices[i]], v[indices[i+1]], v[indices[i+2]]);
		n[indices[i]] += norm;
		n[indices[i+1]] += norm;
		n[indices[i+2]] += norm;
	}
	
	for (int i=0; i<n.size(); i++)
	{
		n[i].normalize();
	}
	
	m->addVertices( v );
	m->addNormals( n );
	m->addTexCoords( uv );
	m->addIndices( indices );
	
	
	return m;
}
