
#pragma once

#include "ofMain.h"
#include "ParticleClouds.h"


 // Leap Motion SDK
#include "Leap.h"
#pragma comment(lib, "Leap.lib") 

using namespace glm;

class ofApp : public ofBaseApp {

public:
    
    void setup();
    void update();
    void draw();
 
    void keyReleased(int key);
    void drawHand(Leap::Hand hand);
    void drawFinger(Leap::Finger finger);

       ofEasyCam camera;
       //----------------------
       // Leap Motion
       Leap::Controller controller;
       Leap::Frame frame;
       Leap::Finger finger;
       Leap::Hand hand,hand2;
    
       //----------------------
       // Setting up the constatns & vectors for the Veil.
       ofVideoPlayer myVideo;
    
       static const int WIDTH = 640;
       static const int HEIGHT = 480;
       static const int PARTICLES_VIDEO = WIDTH * HEIGHT;
       
       ofVec3f myVerts[PARTICLES_VIDEO];
       ofVec3f pointVerts[PARTICLES_VIDEO];

       ofFloatColor myColor[PARTICLES_VIDEO];
       ofFloatColor pointColor[PARTICLES_VIDEO];
       
       ofVbo myVbo;
       ofVbo pointVbo;
           
       bool startingPos; // the fixed position of pixels.

    //----------------------
    // Preparing all my shaders here.
    
       ofShader spaceShader;
       ofShader surfaceShader;
       ofFloatColor matAmbient;
       ofFloatColor matDiffuse;
       ofFloatColor matSpecular;
       float matShininess;
       ofFloatColor lightColor;
       ofImage environmentMap;
       float matReflectivity;
       float matTransparency;
       float refractiveIndex;

    ofImage environmentMapRight;
    ofImage environmentMapLeft;
    
    //----------------------
     // MY FLOATING VARS FOR THE SHADERS
     
     float colourR;
     float colourG;
     float colourB;
     float shaderControl;

    //---------------------
    //-the Veil & Background Ambience.
    
    ofSoundPlayer mySound;
    
    //----------------------
    //-Setting up HARP & CELLO.
    vector <ofSoundPlayer> myHarpSounds; // dynamically allocated array to store sound data. The data type here is : <ofSoundPlayer>
    
    vector <ofSoundPlayer> myCelloSounds; // dynamically allocated array to store sound data. The data type here is : <ofSoundPlayer>
    
    //----------------------
    //-Preparing Vertex Buffer Objects for the partcles.
    ofVboMesh meshLeft;
    ofVboMesh meshRight; 
    static const int NUM = 5000;   // This variable CAN NOT BE modified.
    ParticleClouds particles[NUM];   // Pulling the particle class.

    //----------------------
    //-Instructions for the user.
    ofTexture instructions;
    
    bool activate;

};
