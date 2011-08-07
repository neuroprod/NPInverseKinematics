//
//  Worm.cpp
//  threadExample
//
//  Created by Kris Temmerman on 06/08/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Worm.h"


void Worm::setup()
{
    remove =false;
    type=1;
    if(ofRandom(2)>1) type =0;
    
    mainBone =new Bone();
    mainBone->numSegments =2;
    
    speed =0;
    mainBone->setup();
    noiseScale =ofRandom(30, 200);
    
    float objScale =0.5;
    numSegments =20;
    if(type==1){numSegments =100;
        objScale =0.2;
    
        noiseScale/=5;
    }
    numCircleSegments =20;
    for(int i=0;i<numSegments;i++)
    {
    
        Bone *bone = new Bone();
        bone->numSegments =numCircleSegments;
        bone->size =40*objScale;
        bone->width =15*objScale;
       if(i==2) bone->size =20*objScale;
        if(i==1) bone->size =10*objScale;
        if(i==0) bone->width =0;
        if(i==1) bone->width =10*objScale;
        if(i==2) bone->width =13*objScale;
        
        /*if(i==3) bone->width =70*objScale;
        
        if(i==4) bone->width =80*objScale;
        
        if(i==5) bone->width =70*objScale;
        if(i==6) bone->width =60*objScale;
        
        if(i==7) bone->width =30*objScale;
        */
         if(i==numSegments-1) bone->width =0;
        if(i==numSegments-2) bone->width =5*objScale;
        if(i==numSegments-3) bone->width =10*objScale;
        if(i==numSegments-4) bone->width =12*objScale;
        if(i==numSegments-5) bone->width =13*objScale;
       
        
        bone->setup();
        if(i==0 )
        { bone->parent = mainBone;
        }else
        {
            bone->parent = bones[i-1];
        }
        bones.push_back(bone);
    
    }
       int numindices = (numSegments-1)*numCircleSegments*2*3;
    indices  =new int[numindices];
    vertices =new ofVec3f[numSegments*numCircleSegments] ;
    normals.assign(numSegments*numCircleSegments,ofVec3f());
    normalCount.assign(numSegments*numCircleSegments,0); 
    
    bonePos=new int[numSegments*numCircleSegments] ;
    segmPos=new int[numSegments*numCircleSegments] ;
    
    for (int i=0; i<numSegments*numCircleSegments;i++)
    {
        bonePos[i ]  =floorf(i/numCircleSegments);
        segmPos[i] =i-  bonePos[i ]*numCircleSegments;
        //cout <<bonePos[i ] << " "<<segmPos[i ]<< "\n"; 
    }
    
    for (int i=0; i<numindices/3; i++)
    {
        int pos =i*3;
        indices[pos ] =0;
        indices[pos+1 ] =1 ;
        indices[pos+2 ] =3 ;
    }
    
    int count =0;
    for (int i=0;i<numSegments-1;i++)
    {
    
        for (int j=0;j<numCircleSegments-1;j++)
        {
            
            
            indices [count] = i*numCircleSegments+j;
            indices [count+1] =  i*numCircleSegments+numCircleSegments+j;
            indices [count+2] =i*numCircleSegments+1+j;
            
            indices [count+3] =i*numCircleSegments+1+j; 
            indices [count+4] =i*numCircleSegments+numCircleSegments+j;
            indices [count+5] =  i*numCircleSegments+numCircleSegments+1+j;
           
            count+=6;
            
        
        
        }
       indices [count] = i*numCircleSegments  +numCircleSegments-1;
        indices [count+1] =  i*numCircleSegments +numCircleSegments+numCircleSegments-1;
        indices [count+2] =i*numCircleSegments ;
        
        indices [count+3] =i*numCircleSegments; 
        indices [count+4] =i*numCircleSegments+numCircleSegments+numCircleSegments-1;
        indices [count+5] =  i*numCircleSegments+numCircleSegments;
        
        count+=6;

       
    
    }
    
}
void Worm::update(float spec,float specSize)
{
    moveRoot();
    
    //cout << spec<< " ";
    float st=(spec+specSize)*10;
    st+=1;
    if(type==1)st+=3;
    if(st>speed)speed =st;
    speed*=0.8;
    
    for(int i=0;i<numSegments;i++)
    {
        
        bones[i]->update();
        
    }
    int numVer =numSegments*numCircleSegments;
    for (int i=0;i<numVer;i++)
    {
        //cout << " ---"<< bonePos[i]<< " "<< segmPos[i ]<<"\n";
        vertices[i] = bones[bonePos[i]]->verticesProj [segmPos[i ]]   ;    
    
    
    }
    normals.clear();
    normalCount.clear();
    normals.assign(numSegments*numCircleSegments,ofVec3f());
    normalCount.assign(numSegments*numCircleSegments,0); 
   // cout << "\n";
    calculateNormals();

}
void Worm::calculateNormals()
{
    int numtris = (numSegments-1)*numCircleSegments*2;
    for (int i=0; i<numtris; ++i)
    {
        
        int index0  = indices[i *3];
        int index1  = indices[i *3+1];
        int index2  = indices[i *3+2];
        
        ofVec3f vec0 = vertices[index0];
        ofVec3f vec1 = vertices[index1];
        ofVec3f vec2 = vertices[index2];
        
        ofVec3f v1 = vec0-vec1;
        ofVec3f v2 =vec0-vec2;
      //   cout << v1<< " tessssst\n ";
       ofVec3f n = v1.cross(v2);
        
      
        
        
        
      n.normalize();
        //cout << n << " test\n ";
        normals[index0]+=n;
        normals[index1]+=n;
        normals[index2]+=n ;
        
        
        normalCount[index0]+=1;
        normalCount[index1]+=1;
        normalCount[index2]+=1;
        
    }
    
    for (int i=0; i<numSegments*numCircleSegments;++i)
    {
    
        normals[i]/=normalCount[i];
    
    
    }
}
void Worm::moveRoot()
{
    
    
    ofVec4f pos = mainBone->pos;
    if(pos.squareLength()>1000000 && remove==false)
    {
     
    mainBone->speed+= -pos/1000;
    }
    else if(remove==true)
    {
        mainBone->speed-= -pos/3000;
    }
    
    float dirX = noise->noise(pos.x/noiseScale,pos.y/noiseScale+ofGetFrameNum()/10,pos.z/noiseScale);
    float dirY = noise->noise(pos.x/noiseScale+1000.1,pos.y/noiseScale,pos.z/noiseScale+ofGetFrameNum()/100);
    float dirZ = noise->noise(pos.x/noiseScale+ofGetFrameNum()/noiseScale,pos.y/noiseScale+1000.2,pos.z/noiseScale);
    mainBone->speed.x +=dirX*5;
    mainBone->speed.y +=dirZ*5;
    mainBone->speed.z +=dirY*5;
    mainBone->dir = -mainBone->speed;
    mainBone->dir.normalize();
  
    mainBone->pos+= mainBone->speed*(speed);
    mainBone->speed*=0.95;
    
}

void Worm::draw()
{
    if(type==0){
    
    ofSetHexColor(0xC5D9E0);
    }else{
    ofSetHexColor(0xD18D60);
    }
    int numindices = (numSegments-1)*numCircleSegments*2*3;
    
    ofSeedRandom(1);
    glBegin(GL_TRIANGLES);
    
    for (int i=0; i<numindices/3; i++)
    {
        
        int index0 =indices[i *3];
        int index1 =indices[i*3+1];
        int index2 =indices[i*3+2];
        
        
        //point1
        ofVec3f vec =  vertices[  index0] ;
        ofVec3f norm=  normals[  index0] ;
        
       // glColor3f((norm.x+1)/2,(norm.y+1)/2, (norm.z+1)/2);
 glNormal3f(norm.x,norm.y,norm.z);
        glVertex3f(vec.x,vec.y, vec.z);
        
        
        //point2
        vec =  vertices[  index1] ;
        norm=  normals[  index1] ;

       // glColor3f((norm.x+1)/2,(norm.y+1)/2, (norm.z+1)/2);
         glNormal3f(norm.x,norm.y,norm.z);
        glVertex3f(vec.x,vec.y, vec.z);
        
        
        //point3
        vec =  vertices[  index2] ;
        norm=  normals[  index2] ;
        
       // glColor3f((norm.x+1)/2,(norm.y+1)/2, (norm.z+1)/2);
        glNormal3f(norm.x,norm.y,norm.z);
        glVertex3f(vec.x,vec.y, vec.z);
   
        
        
        
    }
    glEnd();
    
    
    return;
   
     ofSetHexColor(0x555555);
    for(int i=0;i<numSegments;i++)
    {
        
        bones[i]->drawLines();
        
      
    }
    
   
    // cout << verticesProj.size() << " ---";
    for(int i=0;i<numCircleSegments;i++)
    {
      
        glLineWidth(1);
        glColor4f(1, 1, 1, 1);

         glBegin(GL_LINE_STRIP);
        for(int k=0;k<numSegments;k++)
        {
            
          ofVec3f vec =   bones[k ]->verticesProj[i];
        glVertex3f(vec.x, vec.y, vec.z );     
            
        }
        glEnd( );
        
        
        // if(i==0)   cout << "- "<< vp<<" \n";
       
        
    }
    
}
