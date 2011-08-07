//
//  Bone.cpp
//  threadExample
//
//  Created by Kris Temmerman on 06/08/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Bone.h"
void Bone::setup()
{
    
    n=new perlinNoise;
    
    pos.x =ofRandom(-40,50);
    pos.y=ofRandom(-50,50);
    pos.z=ofRandom(-50,50);
    //size =40; 

    
    
    dir.x =1;
    dir.y=0;
    dir.z=0;
    
    speed.x = 0;
    speed.y =0;
    speed.z =0;
   // cout<< vertices.max_size()<< " dd";
    float step = PI*2/numSegments;
    cout << numSegments;
    //numSegments =step;
    for(int i=0;i<numSegments;i++)
    {
        ofVec3f *vec =new ofVec3f() ;
        vec->x = sinf(i*step)*width;
        vec->y = cosf(i*step)*width;
        vec->z =0;
        
       vertices.push_back(vec);
        //ofVec3f vec2
    //verticesProj.push_back(vec2);
    }
    
    
}
void Bone::update()
{
    //pos.x =parent->pos.x+10;
   // pos.y=parent->pos.z;
   // pos.z=parent->pos.y;
    ofVec3f l = pos-parent->pos;
    l.normalize();
   // dir.normalize();
    q.makeRotate(dir,l );
    q.get (rotMatrix);
    
   // cout << q;
   ofVec3f dir2 = rotMatrix.preMult(dir);
    dir2.normalize();
    ofVec3f dir3 = dir2*0.7 + parent->dir*0.3;
// cout << dir  << "      -      "<< dir2 <<"\n";
    dir =dir3;
    dir3*=size;
    pos = parent->pos+dir3;
    verticesProj.clear();
    // cout << rotMatrix <<" \n";
    dir.normalize();
    q.makeRotate(dir,ofVec3f(0,0,1) );
    q.get (rotMatrix);
    float factor = n->noise(pos.x/100,pos.y/100+(float)ofGetFrameNum()/20,pos.z/100);
    factor+=1;
    if(factor<0)factor =0;
    factor*=3;
    for(int i=0;i<numSegments;i++)
    {
        ofVec3f *vec = vertices[i];
       
        ofVec3f vecr =  rotMatrix.postMult(*vec) ;
    // cout << vecr << "      -      "<< *vec <<"\n";
       vecr*=factor;
        vecr+=pos;
        verticesProj.push_back(vecr);
        
    }
}
void Bone::drawLines()
{
    glBegin(GL_LINE_STRIP);
   // cout << verticesProj.size() << " ---";
    for(int i=0;i<numSegments;i++)
    {
       ofVec3f vec = verticesProj[i];
        ofVec3f vp =vec-pos;
       // if(i==0)   cout << "- "<< vp<<" \n";
        glVertex3f(vec.x, vec.y, vec.z );
        
    }
    glEnd( );
}
void Bone::draw()
{
    ofPushView();
    float ra;
    float rx;
    float ry;
    float rz;
    q.getRotate(ra,rx,ry,rz);
    
    ofTranslate(pos);
    ofRotate(ra,rx, ry,rz);
    ofBox  (20);
    ofPopMatrix();
    //
  // ofLine(pos,(dir*size)+pos);
}