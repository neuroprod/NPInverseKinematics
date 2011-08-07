//
//  Bone.h
//  threadExample
//
//  Created by Kris Temmerman on 06/08/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef threadExample_Bone_h
#define threadExample_Bone_h

#include "ofMain.h"
#include "perlinNoise.h"

class Bone
{

public:
    void setup();
    void draw();
    void drawLines();
    void update();
    
    ofVec3f speed;
    ofVec3f pos;
    ofVec3f dir;
    float size;
    Bone *parent;
    int numSegments;
    float width;
    vector<ofVec3f*> vertices;
    vector<ofVec3f> verticesProj;
    
    perlinNoise *n;
    
protected:
    ofQuaternion q;
    ofMatrix4x4 rotMatrix;
    
private:



};


#endif
