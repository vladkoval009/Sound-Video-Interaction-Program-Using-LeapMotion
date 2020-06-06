#pragma once
#include "ofMain.h"

class ParticleClouds {
    
public:
    ParticleClouds();
    void addForce(ofVec3f force);
    void addForce(float forceX, float forceY, float forceZ);
    void update();
    void draw();

    void addRepulsionForce(float x, float y, float z, float radius, float scale);
    void addRepulsionForce(ParticleClouds &p, float radius, float scale);
    
    void addAttractionForce(float x, float y, float z, float radius, float scale);
    void addAttractionForce(ParticleClouds &p, float radius, float scale);
    
    ofVec3f position;
    ofVec3f velocity;
    ofVec3f acceleration;
    float friction;
    float radius;
    float weight;
    float startTime;
};
