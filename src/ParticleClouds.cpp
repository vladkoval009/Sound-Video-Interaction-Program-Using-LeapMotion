//  Created by V Kovalskyi on 25/04/2020.

#include "ParticleClouds.h"

ParticleClouds::ParticleClouds(){
    radius = 10.0;
    friction = 0.01;
    weight = 1.0;
    position.set(ofGetWidth()/2.0, ofGetHeight()/2.0, 0);
    velocity.set(0, 0, 0);
    acceleration.set(0, 0, 0);
    startTime = ofGetElapsedTimef();
}

void ParticleClouds::update(){
    acceleration -= velocity * friction;
    velocity += acceleration;
    position += velocity;
    acceleration.set(0, 0, 0);
}

void ParticleClouds::draw(){
    ofPushMatrix();
    ofTranslate(position);
    ofPoint(0, 0, radius);
    ofPopMatrix();
}

void ParticleClouds::addForce(ofVec3f _force){
    acceleration += _force / weight;
}
void ParticleClouds::addForce(float forceX, float forceY, float forceZ){
    acceleration += ofVec3f(forceX, forceY, forceZ) / weight;
}



void ParticleClouds::addRepulsionForce(float x, float y, float z, float radius, float scale){
    ofVec3f positionVEC3Force;
    positionVEC3Force.set(x,y,z);
    ofVec3f difference = position - positionVEC3Force;
    float length = difference.length();
    bool checkifCLOSE = true;
    if (radius > 0){
        if (length > radius){
            checkifCLOSE = false;
        }
    }
    if (checkifCLOSE == true){
        float p = 1 - (length / radius);
        difference.normalize();
        acceleration = acceleration + difference * scale * p;
    }
}

void ParticleClouds::addRepulsionForce(ParticleClouds &p, float radius, float scale){
    ofVec3f positionVEC3Force;
    positionVEC3Force.set(p.position.x, p.position.y, p.position.z);
    ofVec3f difference = position - positionVEC3Force;
    float length = difference.length();
    bool checkifCLOSE = true;
    if (radius > 0){
        if (length > radius){
            checkifCLOSE = false;
        }
    }
    if (checkifCLOSE == true){
        float p = 1 - (length / radius);
        difference.normalize();
        acceleration = acceleration + difference * scale * p;
    }
}

void ParticleClouds::addAttractionForce(float x, float y, float z, float radius, float scale){
    ofVec3f positionVEC3Force;
    positionVEC3Force.set(x,y,z);
    ofVec3f difference = position - positionVEC3Force;
    float length = difference.length();
    bool checkifCLOSE = true;
    if (radius > 0){
        if (length > radius){
            checkifCLOSE = false;
        }
    }
    if (checkifCLOSE == true){
        float p = 1 - (length / radius);
        difference.normalize();
        acceleration = acceleration - difference * scale * p;
    }
}

void ParticleClouds::addAttractionForce(ParticleClouds &p, float radius, float scale){
    ofVec3f positionVEC3Force;
    positionVEC3Force.set(p.position.x, p.position.y, p.position.z);
    ofVec3f difference = position - positionVEC3Force;
    float length = difference.length();
    bool checkifCLOSE = true;
    if (radius > 0){
        if (length > radius){
            checkifCLOSE = false;
        }
    }
    if (checkifCLOSE == true){
        float p = 1 - (length / radius);
        difference.normalize();
        acceleration = acceleration - difference * scale * p;
    }
}

