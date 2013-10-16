//
// CLOUDS Interactive Documentary
//
// VISUAL SYSTEMS
//
// Welcome to the EMPTY CloudsVisualSystem
//
//
//

#pragma once

#include "CloudsVisualSystem.h"
#include "Cog.h"

class BoundBox{
public:
	BoundBox(){
		minBound.set( 1000000, 1000000, 1000000);
		maxBound.set( -1000000, -1000000, -1000000);
	};
	
	BoundBox(vector<ofVec3f>& v){
		minBound.set( 1000000, 1000000, 1000000);
		maxBound.set( -1000000, -1000000, -1000000);
		
		compute( v );
	};
	
	~BoundBox(){};
	
	void compute( vector<ofVec3f>& v )
	{
		for (vector<ofVec3f>::iterator it=v.begin(); it!=v.end(); it++)
		{
			minBound.x = min( minBound.x, it->x );
			minBound.y = min( minBound.y, it->y );
			minBound.z = min( minBound.z, it->z );
			
			maxBound.x = max( maxBound.x, it->x );
			maxBound.y = max( maxBound.y, it->y );
			maxBound.z = max( maxBound.z, it->z );
		}
		
		centroid = (minBound + maxBound) * .5;
	}
	
	ofVec3f minBound;
	ofVec3f maxBound;
	ofVec3f centroid;
};

//TODO: rename this to your own visual system
class MandalaVisualSystem : public CloudsVisualSystem {
  public:
    
	//TODO: Change this to the name of your visual system
	//This determines your data path so name it at first!
	//ie getVisualSystemDataPath() uses this
    string getSystemName(){
		return "MandalaVisualSystem";
	}

	//These methods let us add custom GUI parameters and respond to their events
    void selfSetupGui();
    void selfGuiEvent(ofxUIEventArgs &e);
    
	//Use system gui for global or logical settings, for exmpl
    void selfSetupSystemGui();
    void guiSystemEvent(ofxUIEventArgs &e);
    
	//use render gui for display settings, like changing colors
    void selfSetupRenderGui();
    void guiRenderEvent(ofxUIEventArgs &e);

	// selfSetup is called when the visual system is first instantiated
	// This will be called during a "loading" screen, so any big images or
	// geometry should be loaded here
    void selfSetup();

	// selfBegin is called when the system is ready to be shown
	// this is a good time to prepare for transitions
	// but try to keep it light weight as to not cause stuttering
    void selfBegin();

	// selfPresetLoaded is called whenever a new preset is triggered
	// it'll be called right before selfBegin() and you may wish to
	// refresh anything that a preset may offset, such as stored colors or particles
	void selfPresetLoaded(string presetPath);
    
	//do things like ofRotate/ofTranslate here
	//any type of transformation that doesn't have to do with the camera
    void selfSceneTransformation();
	
	//normal update call
	void selfUpdate();

	// selfDraw draws in 3D using the default ofEasyCamera
	// you can change the camera by returning getCameraRef()
    void selfDraw();
		
    // draw any debug stuff here
	void selfDrawDebug();

	// or you can use selfDrawBackground to do 2D drawings that don't use the 3D camera
	void selfDrawBackground();

	// this is called when your system is no longer drawing.
	// Right after this selfUpdate() and selfDraw() won't be called any more
	void selfEnd();

	// this is called when you should clear all the memory and delet anything you made in setup
    void selfExit();

	//events are called when the system is active
	//Feel free to make things interactive for you, and for the user!
    void selfKeyPressed(ofKeyEventArgs & args);
    void selfKeyReleased(ofKeyEventArgs & args);
    
    void selfMouseDragged(ofMouseEventArgs& data);
    void selfMouseMoved(ofMouseEventArgs& data);
    void selfMousePressed(ofMouseEventArgs& data);
    void selfMouseReleased(ofMouseEventArgs& data);
	

    // if you use a custom camera to fly through the scene
	// you must implement this method for the transitions to work properly
//	ofCamera& getCameraRef(){
//		return myCustomCamera;
//	}

	//
	ofCamera& getCameraRef(){
		if(videoLoaded){
			return cloudsCamera;
		}
		return CloudsVisualSystem::getCameraRef();
	}
	
	static ofVec3f normalFrom3Points(ofVec3f p0, ofVec3f p1, ofVec3f p2);
	vector<string> getEdgeStrings( ofMesh& m );
	vector<string> getBorderEdges( ofMesh& m );
	ofVboMesh* extrudeSurface( ofVboMesh& surface );
	ofVboMesh* createMeshFromProfile( vector<ofVec3f> profile, ofVec3f offset = ofVec3f(0, 0, 10), bool centerVertices=true );
//	ofVboMesh* createBoxMesh( float _w, float _h, float _z, int _subx, int _suby, int _subz );
	static ofVboMesh* createBoxMesh( float low_w, float hi_w, float low_h, float hi_h, float low_d, float hi_d, int _subx, int _suby, int _subz );
	
	static ofVboMesh* createCog( float uRadiansMin, float uRadiansMax, float vRadiansMin, float vRadiansMax, float thickness, int subdX, int subdY );
	
	
	void deleteMesh( ofVboMesh* m );
	
	void loadShaders();
	
	BoundBox getBoundBox( ofMesh& m );
	
	void drawMandala();

protected:
    
    //  our Stuff
	ofxUISuperCanvas* customGui;
	
	bool videoLoaded;
	ofImage someImage;
	ofShader pointcloudShader;
	ofVboMesh simplePointcloud;
	
	float spread;
	
	ofTessellator tesselator;
	vector<ofVboMesh*> meshes;
	
	ofPolyline polyline;
	ofVboMesh polyMesh;
	
	//shaders
	ofShader normalShader;
	ofShader deformerShader;
	ofShader deformedAndTextured;
	
	vector<Cog*> cogs;
	
	vector <ofImage> images;
	
};