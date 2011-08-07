//
//  Worm.h
//  threadExample
//
//  Created by Kris Temmerman on 06/08/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef threadExample_Worm_h
#define threadExample_Worm_h

#include "ofMain.h"
#include "Bone.h"
#include "perlinNoise.h"

class Worm
{

public:

    void setup();
    void update(float spec,float specsize);
    void draw();
bool remove;
protected:
    
    void moveRoot();
    void calculateNormals();
    float speed;
    vector<Bone *> bones;
    Bone *mainBone;
    perlinNoise *noise;
    
    int numSegments;
    int numCircleSegments;
    float noiseScale;
    int type;
    
    int *indices;
    ofVec3f *vertices;
    vector <ofVec3f> normals;
    vector <int> normalCount;
    int *bonePos;
    int *segmPos;
    
private:

};


#endif
