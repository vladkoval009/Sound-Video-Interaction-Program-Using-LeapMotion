
#include "ofApp.h"


 //--------------------------------------------------------------
 void ofApp::setup() {
     
     camera.setDistance(750);
     
     
     // My Little Bool for Instructions.
     activate = false;
     // Loading Instructions.
     ofLoadImage(instructions, "imageAssets/instruction.png");
     
    //====================Enabling the required gestures for Leap Motion==//
     
     controller.enableGesture(Leap::Gesture::TYPE_SWIPE);
     controller.enableGesture(Leap::Gesture::TYPE_KEY_TAP);
     
    //====================Setting up Ambient Sound========================//
     
    mySound.load("ambience.mp3");
    mySound.setVolume(0.7);
    mySound.play();
    
    //=====================Variables Initializing for the SHADERS=========//
     
     shaderControl = 0.5;
     colourR = 150;
     colourG = 130;
     colourB = 100;
     
    //=====================VIDEO Veil Initializing========================//
   
     myVideo.load("videoAssets/thunderWaves.mp4");
     myVideo.play();
     startingPos = true;
     
     //=====================HARP SOUND Initializing=======================//
     
     // A one time initialization putting my data into the array.

     string myHarpSoundsArray[] = {"harpSoundMP3/harpA2.mp3", "harpSoundMP3/harpA4.mp3", "harpSoundMP3/harpA6.mp3", "harpSoundMP3/harpB3.mp3","harpSoundMP3/harpB5.mp3","harpSoundMP3/harpB6.mp3","harpSoundMP3/harpC5.mp3","harpSoundMP3/harpD4.mp3","harpSoundMP3/harpD4.mp3" "harpSoundMP3/harpE3.mp3","harpSoundMP3/harpE5.mp3"};
     
     for (int i = 0; i < 11; i++) {
     
     ofSoundPlayer playHarp;
         playHarp.load(myHarpSoundsArray[i]);
             playHarp.setVolume(0.5);
             playHarp.setMultiPlay(true);
             myHarpSounds.push_back(playHarp); // pushing elements into my <vector>. I can populate this array as I go with new data.
         
     };
     
     //=====================CELLO SOUND Initializing==================//

     // A one time initialization putting my data into the array.

     string myCelloSoundArray[] = {"celloSoundsMP3/Cello1.mp3","celloSoundsMP3/Cello1.mp3","celloSoundsMP3/Cello2.mp3","celloSoundsMP3/Cello3.mp3","celloSoundsMP3/Cello4.mp3","celloSoundsMP3/Cello5.mp3","celloSoundsMP3/Cello6.mp3",};
     
     for (int i = 0; i < 6; i++) {
         
         ofSoundPlayer playCello;
             playCello.load(myCelloSoundArray[i]);
                 playCello.setVolume(0.2); // Cello is very loud so I turned the volume down.
                 playCello.setMultiPlay(true);
                 myCelloSounds.push_back(playCello); // pushing data into my <vector>. I can populate this array as I go with new data.
             
     };
    
     
     //====================SHADERS====================================//

     ofDisableArbTex();
     
     // One shader is used for both sets of particles. Right & Left Hands. Only the Enviromental is different for each of them.
     
     environmentMapRight.load("imageAssets/mercury.jpg");
     environmentMapLeft.load("imageAssets/copper.png");
     
    surfaceShader.load("shaders/simplePhong");
    matAmbient.set(0.1, 0.1, 0.2);
    matDiffuse.set(0.2, 0.5, 0.7);
    matSpecular.set(3.5, 4.0, 5.0);
    matShininess = 900;
    lightColor.set(1.0, 1.0, 0.8);
    matReflectivity = 0.7;
    matTransparency = 1.0;
    refractiveIndex = 1.43;
     
    //***********************************************
     
     spaceShader.load("shaders/spaceShader");
     
    //====================PARTICLES Initialization ^_^=============

    for (int i = 0; i < NUM; i++) {
        
           particles[i].position.set(ofRandom(-ofGetWidth()/2.0, ofGetWidth()/2.0),
                                     ofRandom(-ofGetHeight()/2.0, ofGetHeight()/2.0),
                                     ofRandom(-ofGetHeight()/2.0, ofGetHeight()/2.0));
           // Random positioning on XYZ.
           particles[i].friction = 0.005; // Let's make the motion smooth! Set to 0.005!

    };
     
    //====================MESH particles Initialization *_*===================
     
       meshLeft.setMode(OF_PRIMITIVE_POINTS);
       static GLfloat DIS[] = { 0.0, 0.0, 1.0 };
       glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, DIS);
     
     
       meshRight.setMode(OF_PRIMITIVE_POINTS);
       static GLfloat DIS_TWO[] = { 0.0, 0.0, 1.0 };
       glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, DIS_TWO);
         

 };

 //--------------------------------------------------------------
 void ofApp::update() {
 
     ofSetWindowTitle(ofToString(ofGetFrameRate())); // Checking the performance of the app.
     
     controller.isConnected(); // this line is needed to call the leap gestures. Possibly the code needs green light that leap is connected to my computer.

     frame = controller.frame();
     
     myVideo.update();
    
     //=====================LEAP GESTURES=======================

          const Leap::GestureList& gestures = frame.gestures();
          
          for (int i = 0; i < gestures.count(); i++) {

              const Leap::Gesture& gesture = gestures[i];
              Leap::Gesture::Type type = gesture.type();

              if (type == Leap::Gesture::Type::TYPE_SWIPE) {
                  
                  shaderControl += shaderControl <= 1 ? 0.03 : 0;
                  } else {
                  shaderControl -= shaderControl > 0 ? 0.03 : 0;


                  };

              if ( type == Leap::Gesture::Type::TYPE_KEY_TAP)
              {
                    
                  colourR += colourR > 3 ? 0.9 : 0;
                  colourG += colourG > 5 ? 0.5 : 1;
                  colourB += colourB > 3 ? 0.2 : 0;
              };
              
              
          };
     
     //==========================Picking the hands & fingers for the veil===========
          
     for(int i=0; i<frame.hands().count(); i++) {
         hand = frame.hands()[0];
         hand2 = frame.hands()[1];
         for(int j=0; j<hand.fingers().count() + hand2.fingers().count(); j++) {
             
             finger = frame.fingers()[j];
             
         };
     };
     
    //================The mysterious veil===================

       if (myVideo.isFrameNew()) {
           ofPixels pixelsVBO_1;
           pixelsVBO_1 = myVideo.getPixels();
           for (int i = 0; i < WIDTH; i++) {
               for (int j = 0; j < HEIGHT; j++) {
                   float r = (float)pixelsVBO_1[(int)(j * myVideo.getWidth() * 3 + i * 3)] /256.0;
                   float g = (float)pixelsVBO_1[(int)(j * myVideo.getWidth() * 3 + i * 3 + 1)] /256.0;
                   float b = (float)pixelsVBO_1[(int)(j * myVideo.getWidth() * 3 + i * 3 + 2)] /256.0;

                   float brightness = (r + g + b) / 3.0f ;

                   myColor[j * WIDTH + i] = ofFloatColor(r,g,b,1.0);
                   if(startingPos == false)
                       
                   myVerts[j * WIDTH + i] = ofVec3f(i-WIDTH/2, j-HEIGHT/2,brightness*finger.tipPosition().z);
                   else myVerts[j * WIDTH + i] = ofVec3f(i-WIDTH/2, j-HEIGHT/2,0);
                   
                   int size = sizeof(pixelsVBO_1);
                   
               }
           }
           
           myVbo.setVertexData(myVerts,PARTICLES_VIDEO,GL_DYNAMIC_DRAW_ARB);
           myVbo.setColorData(myColor,PARTICLES_VIDEO,GL_DYNAMIC_DRAW_ARB);
           
           };
 
     
//=========================HARP UPDATE===============================================
     

     for (Leap::Hand hand : frame.hands()) {
        if(hand.isRight()){
         for (Leap::Finger finger : hand.fingers()) {

             ofVec3f velocity = ofVec3f(finger.tipVelocity().x, -finger.tipVelocity().y, finger.tipVelocity().z);

             if (velocity.length() > 512) {

                 myHarpSounds[ofGetFrameNum() % 11].play(); // % BY THE NUMBER OF A AUDIO FILES.
           };
         };
        };
       };
     
//=========================CELLO UPDATE===============================================
     
         for (Leap::Hand hand : frame.hands()) {
             if(hand.isLeft()){
              for (Leap::Finger finger : hand.fingers()) {

                  ofVec3f velocity = ofVec3f(finger.tipVelocity().x, -finger.tipVelocity().y, finger.tipVelocity().z);

                  if (velocity.length() > 512) {

                      myCelloSounds[ofGetFrameNum() % 6].play(); // % BY THE NUMBER OF A AUDIO FILES.
                      
                };
              };
             };
            };
     
     //=======================UPDATING MESH & PARTICLES================================
     
     //=======================FOR THE LEFT HAND========================================
     
        for (Leap::Hand hand : frame.hands()) {

            if(hand.isLeft()){

               for (Leap::Finger finger : hand.fingers() ) {

                   if (finger.type() == Leap::Finger::TYPE_INDEX) {

        meshLeft.clear();

        for (int i = 0; i < NUM; i++) {
            particles[i].addAttractionForce(finger.tipVelocity().x,finger.tipVelocity().y, finger.tipVelocity().z,ofGetWidth(), 0.5);

            particles[i].update();
            meshLeft.addVertex(particles[i].position);
        };

                   };
               };
            };
        };
     
     //=======================FOR THE RIGHT HAND========================================

             for (Leap::Hand hand : frame.hands()) {

                 if(hand.isRight()){

                    for (Leap::Finger finger : hand.fingers() ) {

                        if (finger.type() == Leap::Finger::TYPE_INDEX) {

             meshRight.clear();

             for (int i = 0; i < NUM; i++) {
                 particles[i].addAttractionForce(finger.tipVelocity().x,finger.tipVelocity().y, finger.tipVelocity().z,ofGetWidth(), 0.5);

                 particles[i].update();
                 meshRight.addVertex(particles[i].position);
             };
                        };
                    };
                 };
             };

 };

//--------------------------------------------------------------

 void ofApp::draw() {
     
     glEnable(GL_DEPTH_TEST);
     
     camera.begin();
     
     
       //===========================================
     
     if ( activate == false)
     {
     ofPushMatrix();
     ofScale(1, 1);
     ofSetColor(255, 255, 255, 255);
     instructions.draw(-500, -400, 80, 1024, 768);
     ofPopMatrix();
     }
          
       //===========================================

     
     // Drawing hands.
        ofPushMatrix();
        frame = controller.frame();
        for (Leap::Hand hand : frame.hands()) {
            ofSetColor(255);
            drawHand(hand);
        };
        ofPopMatrix();

     
     //=============================================

         ofPushMatrix();
         glPointSize(0.3);
         ofScale(3, 3, 3);
         ofTranslate(0, 0, 0);
         myVbo.draw(GL_POINTS,0,PARTICLES_VIDEO);
         ofPopMatrix();

    //=============================================
     
    
     //********************************************************
     
       spaceShader.begin();
       spaceShader.setUniform1f("colourR", colourR);
       spaceShader.setUniform1f("colourG", colourG);
       spaceShader.setUniform1f("colourB", colourB);

       spaceShader.setUniform1f("shaderControl", shaderControl);
       spaceShader.setUniform1f("time", ofGetElapsedTimef()/4);
       spaceShader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());

        ofPushMatrix();
        ofSetCylinderResolution(40, 40);
        ofDrawCylinder(-100, -100, -300, 1500, 1500);
        ofPopMatrix();
     
     spaceShader.end();

     //********************************************************
     
     ofRotateXDeg(ofGetElapsedTimef()*2); // Rotating the clouds to observe even without interaction.
     
     // Manupulation Left Hand.
     
     surfaceShader.begin();
              surfaceShader.setUniform4f("matAmbient", matAmbient);
              surfaceShader.setUniform4f("matDiffuse", matDiffuse);
              surfaceShader.setUniform4f("matSpecular", matSpecular);
              surfaceShader.setUniform1f("matShininess", matShininess);
              surfaceShader.setUniform4f("lightColor", lightColor);
              surfaceShader.setUniform1f("matReflectivity", matReflectivity);
              surfaceShader.setUniformTexture("environmentMap", environmentMapLeft.getTexture(), 1);
              surfaceShader.setUniform1f("matTransparency", matTransparency);
              surfaceShader.setUniform1f("matRefractiveIndex", refractiveIndex);
     
        ofPushMatrix();
        glPointSize(10);
        meshLeft.draw();
        ofPopMatrix();
     
     surfaceShader.end();

     // Manupulation Right Hand.
     
     surfaceShader.begin();
          surfaceShader.setUniform4f("matAmbient", matAmbient);
          surfaceShader.setUniform4f("matDiffuse", matDiffuse);
          surfaceShader.setUniform4f("matSpecular", matSpecular);
          surfaceShader.setUniform1f("matShininess", matShininess);
          surfaceShader.setUniform4f("lightColor", lightColor);
          surfaceShader.setUniform1f("matReflectivity", matReflectivity);
          surfaceShader.setUniformTexture("environmentMap", environmentMapRight.getTexture(), 1);
          surfaceShader.setUniform1f("matTransparency", matTransparency);
          surfaceShader.setUniform1f("matRefractiveIndex", refractiveIndex);
     
       ofPushMatrix();
       glPointSize(10);
       meshRight.draw();
       ofPopMatrix();
     
     surfaceShader.end();

     
     //********************************************************

       
     camera.end();
     
 }
  
 //--------------------------------------------------------------
 //-Drawing the Hands--------------------------------------------
void ofApp::drawHand(Leap::Hand hand) {

 
    Leap::FingerList fingers = hand.fingers();
    for (int j = 0; j < fingers.count(); j++) {
        this->drawFinger(fingers[j]);
    }
 
    ofPushMatrix();
    ofVec3f palm = ofVec3f(hand.palmPosition().x, hand.palmPosition().y, hand.palmPosition().z);
    ofTranslate(palm);
    ofDrawSphere(5);
    ofPopMatrix();
}
 
//--------------------------------------------------------------
void ofApp::drawFinger(Leap::Finger finger) {
 
    ofVec3f tip = ofVec3f(finger.tipPosition().x, finger.tipPosition().y, finger.tipPosition().z);
    ofPushMatrix();
    ofTranslate(tip);
    ofDrawSphere(5);
    ofPopMatrix();
 
    ofVec3f base = ofVec3f(tip.x + finger.direction().x * finger.length(),
        tip.y + finger.direction().y * finger.length() - 1,
        tip.z + finger.direction().z * finger.length() - 1);
    ofPushMatrix();
    ofTranslate(base);
    ofDrawSphere(5);
    ofPopMatrix();
 
    ofDrawLine(tip, base);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    if (key == ' ') {

        activate = true;
    }
}
 
