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
	
	//defaults
	mandalaGlobalScale.set(1,1,1);
	
	
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
	
	for (int i=0; i<images.size(); i++) {
		textures.push_back( &images[i].getTextureReference() );
	}
	
	vid.loadMovie(getVisualSystemDataPath() + "images/aliens.gif" );
	vid.play();
	textures.push_back( &vid.getTextureReference() );
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
	vid.update();
}

// selfDraw draws in 3D using the default ofEasyCamera
// you can change the camera by returning getCameraRef()
void MandalaVisualSystem::selfDraw()
{
	ofPushMatrix();
	ofScale( mandalaGlobalScale.x, mandalaGlobalScale.y, mandalaGlobalScale.z );
	
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
	
	ofPopMatrix();
}

void MandalaVisualSystem::drawMandala()
{
	for (int i=0; i<cogs.size(); i++) {
		float rotY = ofGetElapsedTimef() * cogs[i]->radius;
		ofPushMatrix();
		ofRotate( rotY, 0, 1, 0);
		
		if(i%2){
			cogs[i]->frontTexture = textures[i%textures.size()];
			cogs[i]->sideTexture = textures[(i+1)%textures.size()];
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

void MandalaVisualSystem::loadShaders()
{
	normalShader.load( getVisualSystemDataPath() + "shaders/normalShader");
	deformerShader.load( getVisualSystemDataPath() + "shaders/deformer");
	
	deformedAndTextured.load( getVisualSystemDataPath() + "shaders/deformer.vert", getVisualSystemDataPath() + "shaders/CogTextured.frag");
}
