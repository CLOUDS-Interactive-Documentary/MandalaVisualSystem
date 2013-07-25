//
//  CloudsVisualSystemEmpty.cpp
//

#include "CloudsVisualSystemEmpty.h"

//These methods let us add custom GUI parameters and respond to their events
void CloudsVisualSystemEmpty::selfSetupGui(){

	customGui = new ofxUISuperCanvas("CUSTOM", gui);
	customGui->copyCanvasStyle(gui);
	customGui->copyCanvasProperties(gui);
	customGui->setName("Custom");
	customGui->setWidgetFontSize(OFX_UI_FONT_SMALL);
	
	customGui->addSlider("Custom Float 1", 1, 1000, &customFloat1);
	customGui->addSlider("Custom Float 2", 1, 1000, &customFloat2);
	customGui->addButton("Custom Button", false);
	customGui->addToggle("Custom Toggle", &customToggle);
	
	guis.push_back(customGui);
	guimap[customGui->getName()] = customGui;
	
}

void CloudsVisualSystemEmpty::selfGuiEvent(ofxUIEventArgs &e){
	
}

//Use system gui for global or logical settings, for exmpl
void CloudsVisualSystemEmpty::selfSetupSystemGui(){
	
}

void CloudsVisualSystemEmpty::guiSystemEvent(ofxUIEventArgs &e){
	
}
//use render gui for display settings, like changing colors
void CloudsVisualSystemEmpty::selfSetupRenderGui(){
	
}

void CloudsVisualSystemEmpty::guiRenderEvent(ofxUIEventArgs &e){
	
}

// selfSetup is called when the visual system is first instantiated
// This will be called during a "loading" screen, so any big images or
// geometry should be loaded here
void CloudsVisualSystemEmpty::selfSetup(){
//	someImage.loadImage( getVisualSystemDataPath() + "images/someImage.png";
}

// selfBegin is called when the system is ready to be shown
// this is a good time to prepare for transitions
// but try to keep it light weight as to not cause stuttering
void CloudsVisualSystemEmpty::selfBegin(){
	
}
// selfPresetLoaded is called whenever a new preset is triggered
// it'll be called right before selfBegin() and you may wish to
// refresh anything that a preset may offset, such as stored colors or particles
void CloudsVisualSystemEmpty::selfPresetLoaded(string presetPath){
	
}
//do things like ofRotate/ofTranslate here
//any type of transformation that doesn't have to do with the camera
void CloudsVisualSystemEmpty::selfSceneTransformation(){
	
}
//normal update call
void CloudsVisualSystemEmpty::selfUpdate(){
	
}
// selfDraw draws in 3D using the default ofEasyCamera
// you can change the camera by returning getCameraRef()
void CloudsVisualSystemEmpty::selfDraw(){
	
}
// draw any debug stuff here
void CloudsVisualSystemEmpty::selfDrawDebug(){
	
}
// or you can use selfDrawBackground to do 2D drawings that don't use the 3D camera
void CloudsVisualSystemEmpty::selfDrawBackground(){
	
}
// this is called when your system is no longer drawing.
// Right after this selfUpdate() and selfDraw() won't be called any more
void CloudsVisualSystemEmpty::selfEnd(){
	
}
// this is called when you should clear all the memory and delet anything you made in setup
void CloudsVisualSystemEmpty::selfExit(){
	
}

//events are called when the system is active
//Feel free to make things interactive for you, and for the user!
void CloudsVisualSystemEmpty::selfKeyPressed(ofKeyEventArgs & args){
	
}
void CloudsVisualSystemEmpty::selfKeyReleased(ofKeyEventArgs & args){
	
}

void CloudsVisualSystemEmpty::selfMouseDragged(ofMouseEventArgs& data){
	
}

void CloudsVisualSystemEmpty::selfMouseMoved(ofMouseEventArgs& data){
	
}

void CloudsVisualSystemEmpty::selfMousePressed(ofMouseEventArgs& data){
	
}

void CloudsVisualSystemEmpty::selfMouseReleased(ofMouseEventArgs& data){
	
}