//
//  MandalaVisualSystem.cpp
//

#include "MandalaVisualSystem.h"
#include "CloudsRGBDVideoPlayer.h"

//#include "CloudsRGBDVideoPlayer.h"
//#ifdef AVF_PLAYER
//#include "ofxAVFVideoPlayer.h"
//#endif

//These methods let us add custom GUI parameters and respond to their events
void MandalaVisualSystem::selfSetupGui(){

	customGui = new ofxUISuperCanvas("CUSTOM", gui);
	customGui->copyCanvasStyle(gui);
	customGui->copyCanvasProperties(gui);
	customGui->setName("Custom");
	customGui->setWidgetFontSize(OFX_UI_FONT_SMALL);
	
	

	
	ofAddListener(customGui->newGUIEvent, this, &MandalaVisualSystem::selfGuiEvent);
	guis.push_back(customGui);
	guimap[customGui->getName()] = customGui;
}

void MandalaVisualSystem::selfGuiEvent(ofxUIEventArgs &e){

}

//Use system gui for global or logical settings, for exmpl
void MandalaVisualSystem::selfSetupSystemGui(){
	
}

void MandalaVisualSystem::guiSystemEvent(ofxUIEventArgs &e){
	
}
//use render gui for display settings, like changing colors
void MandalaVisualSystem::selfSetupRenderGui(){

}

void MandalaVisualSystem::guiRenderEvent(ofxUIEventArgs &e){
	
}

// selfSetup is called when the visual system is first instantiated
// This will be called during a "loading" screen, so any big images or
// geometry should be loaded here
void MandalaVisualSystem::selfSetup(){
	
	videoLoaded = false;

	//getVisualSystemDataPath() + "images/someImage.png";
	
	//shader setup
	loadShaders();
		
	//create some cogs
	for (int i=0; i<10; i++) {
		cogs.push_back( new Cog(1, 1, .1 * i, .09, .2, .6) );
		if(i%2)	cogs.push_back( new Cog(3, 2, .1 * i, .09, .2, .6) );
		if(i%4) cogs.push_back( new Cog(8, 2, .1 * i, .09, .2, .6) );
		
		cogs.push_back( new Cog(12, 1, .1 * i, .09, .2, .6) );
		if(i%2)	cogs.push_back( new Cog(14, 1, .1 * i, .09, .2, .6) );
		if(i%4) cogs.push_back( new Cog(16, 1, .1 * i, .09, .2, .2) );
		
		if(i%2) cogs.push_back( new Cog(18, 3, .1 * i, .09, .2, .7) );
		cogs.push_back( new Cog(22, 10, .1 * i, .09, .2, .3) );
		if(i%3)cogs.push_back( new Cog( 33, 30, .1 * i, .09, .4, .1) );
		cout << cogs.size() << endl;
	}
	
	
	images.resize(4);
	
	images[0].loadImage( getVisualSystemDataPath() + "images/elsaHat.png" );
	images[1].loadImage( getVisualSystemDataPath() + "images/germanBirdRamp.jpg" );
	images[2].loadImage( getVisualSystemDataPath() + "images/greenFatBird.jpg" );
	images[3].loadImage( getVisualSystemDataPath() + "images/laser-eyes1.jpg" );
}

// selfPresetLoaded is called whenever a new preset is triggered
// it'll be called right before selfBegin() and you may wish to
// refresh anything that a preset may offset, such as stored colors or particles
void MandalaVisualSystem::selfPresetLoaded(string presetPath){
	
}

// selfBegin is called when the system is ready to be shown
// this is a good time to prepare for transitions
// but try to keep it light weight as to not cause stuttering
void MandalaVisualSystem::selfBegin(){
	
}

//do things like ofRotate/ofTranslate here
//any type of transformation that doesn't have to do with the camera
void MandalaVisualSystem::selfSceneTransformation(){
	
}

//normal update call
void MandalaVisualSystem::selfUpdate()
{

}

// selfDraw draws in 3D using the default ofEasyCamera
// you can change the camera by returning getCameraRef()
void MandalaVisualSystem::selfDraw()
{
	ofEnableAlphaBlending();
	
	glLineWidth( 2 );
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	

	glEnable(GL_DEPTH_TEST);
//	glDisable(GL_DEPTH_TEST);
//	glDepthFunc(GL_GREATER);
	
	
	glClearDepth(1.);
	glDepthFunc(GL_LESS);
	
	drawMandala();
	
	
	glClearDepth(1.);
	glDepthFunc(GL_LESS);
	
	glCullFace(GL_BACK);
	drawMandala();
	
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	
	

}

void MandalaVisualSystem::drawMandala()
{
	for (int i=0; i<cogs.size(); i++) {
		float rotY = ofGetElapsedTimef() * cogs[i]->radius;
		ofPushMatrix();
		ofRotate( rotY, 0, 1, 0);
		
		if(i%2){
			cogs[i]->frontTexture = &images[i%4].getTextureReference();
			cogs[i]->sideTexture = &images[(i+1)%4].getTextureReference();
			cogs[i]->draw( &deformedAndTextured );
		}
		else{
			cogs[i]->drawBorders( &deformerShader );
		}
		
		ofPopMatrix();
	}
}

// draw any debug stuff here
void MandalaVisualSystem::selfDrawDebug(){
	
	glLineWidth( 4 );
	ofSetColor(255,0,0);
	ofLine(-100, 0,0, 100, 0,0);
	ofSetColor(0,255,0);
	ofLine(0,-100, 0, 0,100,0);
	ofSetColor(0,0,255);
	ofLine(0,0,-100, 0,0,100);
}
// or you can use selfDrawBackground to do 2D drawings that don't use the 3D camera
void MandalaVisualSystem::selfDrawBackground(){

	//turn the background refresh off
	//bClearBackground = false;
	
}
// this is called when your system is no longer drawing.
// Right after this selfUpdate() and selfDraw() won't be called any more
void MandalaVisualSystem::selfEnd(){
	
	simplePointcloud.clear();
	
}
// this is called when you should clear all the memory and delet anything you made in setup
void MandalaVisualSystem::selfExit()
{
	for (vector<ofVboMesh*>::iterator it = meshes.begin(); it != meshes.end(); it++) {
		(*it)->clear();
	}
	
	for (vector<Cog*>::iterator it = cogs.begin(); it != cogs.end(); it++) {
		(*it)->clear();
	}
	
	for (int i=0; i<images.size(); i++) {
		images[i].clear();
	}
}

//events are called when the system is active
//Feel free to make things interactive for you, and for the user!
void MandalaVisualSystem::selfKeyPressed(ofKeyEventArgs & args)
{
	if(args.key == 'l' || args.key == 'L' )
	{
		loadShaders();
	}
}
void MandalaVisualSystem::selfKeyReleased(ofKeyEventArgs & args){
	
}

void MandalaVisualSystem::selfMouseDragged(ofMouseEventArgs& data){
	
}

void MandalaVisualSystem::selfMouseMoved(ofMouseEventArgs& data){
	
}

void MandalaVisualSystem::selfMousePressed(ofMouseEventArgs& data){
	
}

void MandalaVisualSystem::selfMouseReleased(ofMouseEventArgs& data){
	
}

ofVec3f MandalaVisualSystem::normalFrom3Points(ofVec3f p0, ofVec3f p1, ofVec3f p2)
{
	ofVec3f norm = (p2 - p1).cross( p0 - p1);
	return norm.normalized();
}

vector<string> MandalaVisualSystem::getEdgeStrings( ofMesh& m )
{
	vector<string> e( m.getIndices().size() );
	vector<ofIndexType>& indices = m.getIndices();
	
	for (int i=0; i<indices.size(); i+=3)
	{
//		e[i+0] = ofToString( min(indices[i], indices[i+1]) ) + "_" + ofToString( max(indices[i], indices[i+1]) );
//		e[i+1] = ofToString( min(indices[i+1], indices[i+2]) ) + "_" + ofToString( max(indices[i+1], indices[i+2]) );
//		e[i+2] = ofToString( min(indices[i], indices[i+2]) ) + "_" + ofToString( max(indices[i], indices[i+2]) );
		
		e[i+0] = ofToString( indices[i] ) + "_" + ofToString( indices[i+1] );
		e[i+1] = ofToString( indices[i+1] ) + "_" + ofToString( indices[i+2] );
		e[i+2] = ofToString( indices[i+2] ) + "_" + ofToString( indices[i] );
	}
	
	return e;
}

vector<string> MandalaVisualSystem::getBorderEdges( ofMesh& m )
{
	vector<string> borderEdges;
	map<string, int> edgeMap;
	
	vector<ofIndexType>& indices = m.getIndices();
	
	string e0,e1,e2;
	for (int i=0; i<indices.size(); i+=3)
	{
		e0 = ofToString( min(indices[i], indices[i+1]) ) + "_" + ofToString(max(indices[i], indices[i+1]) );
		e1 = ofToString( min(indices[i+1], indices[i+2]) ) + "_" + ofToString(max(indices[i+1], indices[i+2]) );
		e2 = ofToString( min(indices[i], indices[i+2]) ) + "_" + ofToString(max(indices[i], indices[i+2]) );
		
		edgeMap[e0] = edgeMap.find(e0) != edgeMap.end() ? edgeMap[e0] + 1 : 1;
		edgeMap[e1] = edgeMap.find(e1) != edgeMap.end() ? edgeMap[e1] + 1 : 1;
		edgeMap[e2] = edgeMap.find(e2) != edgeMap.end() ? edgeMap[e2] + 1 : 1;
	}
	
	for (map<string, int>::iterator it = edgeMap.begin(); it!=edgeMap.end(); it++) {
		if(it->second == 1){
			borderEdges.push_back( it->first );
		}
	}
	
	return borderEdges;
}


ofVboMesh* MandalaVisualSystem::createMeshFromProfile( vector<ofVec3f> profile, ofVec3f offset, bool centerVertices )
{
	//create polyline out of our contour
	ofPolyline pl;
	pl.addVertices( profile );
	
	//create a tubular mesh by extruding the curve. how do we cap our holes?
	ofVboMesh* m = new ofVboMesh;
	
	//teselate our polyline
	tesselator.tessellateToMesh( pl, OF_POLY_WINDING_POSITIVE, *m );

	vector<ofVec3f>& plv = pl.getVertices();
	vector<ofVec3f>& v = m->getVertices();
	vector<ofIndexType>& indices = m->getIndices();
	
	vector<ofVec3f> capVertices = m->getVertices();
	int capIndexCount = indices.size();
	
	//lofeted borders
	for (int i=0; i<plv.size()-1; i++)
	{
		//border triangle vertices
		int nextIndex = v.size();
		m->addVertex( plv[i] );
		m->addVertex( plv[i+1] );
		m->addVertex( plv[i+1] + offset );
		m->addVertex( plv[i] + offset );
		
		//border triangle indices
		m->addIndex( nextIndex );
		m->addIndex( nextIndex + 1);
		m->addIndex( nextIndex + 2);
		
		m->addIndex( nextIndex );
		m->addIndex( nextIndex + 2);
		m->addIndex( nextIndex + 3);
	}
	
	//other cap with flipped normals
	for (int i=0; i<capIndexCount; i+=3)
	{
		//cap vertices
		int nextIndex = v.size();
		m->addVertex( v[indices[i] ] + offset);
		m->addVertex( v[indices[i+1] ] + offset);
		m->addVertex( v[indices[i+2] ] + offset);
		
		//cap indices
		m->addIndex( nextIndex );
		m->addIndex( nextIndex+2 );
		m->addIndex( nextIndex+1 );
	}
	
	//compute smoothed normals
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
	m->addNormals( n );
	
	if(centerVertices)
	{
		BoundBox bb(v);
		
		for (int i=0; i<v.size(); i++)
		{
			m->setVertex( i, v[i] - bb.centroid);
		}
		
	}
	
	return m;
}

BoundBox MandalaVisualSystem::getBoundBox( ofMesh& m )
{
	return BoundBox( m.getVertices() );
}

void MandalaVisualSystem::loadShaders()
{
	normalShader.load( getVisualSystemDataPath() + "shaders/normalShader");
	deformerShader.load( getVisualSystemDataPath() + "shaders/deformer");
	
	deformedAndTextured.load( getVisualSystemDataPath() + "shaders/deformer.vert", getVisualSystemDataPath() + "shaders/CogTextured.frag");
}

void MandalaVisualSystem::deleteMesh( ofVboMesh* m )
{
	for(int i=meshes.size()-1; i>=0; i--)
	{
		if(meshes[i] == m )
		{
			m->clear();
			meshes.erase( meshes.begin() + i );
		}
	}
}

ofVboMesh* MandalaVisualSystem::createCog( float uRadiansMin, float uRadiansMax, float vRadiansMin, float vRadiansMax, float thickness, int subdX, int subdY )
{
	return createBoxMesh(uRadiansMin, uRadiansMax, vRadiansMin, vRadiansMax, 0, thickness, subdX, subdY, 1 );
}

ofVboMesh* MandalaVisualSystem::createBoxMesh( float low_w, float hi_w, float low_h, float hi_h, float low_d, float hi_d, int _subx, int _suby, int _subz )
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
