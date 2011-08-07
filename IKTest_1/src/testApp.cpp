#include "testApp.h"

bool locked = false;

//--------------------------------------------------------------
void testApp::setup(){
	startCount =0;
    ofBackground(5,5,5);
   ofSetFrameRate(30);
	//TO.start();
    numWorms= 150;
    
    for (int i=0; i<numWorms; i++) {
        Worm *w =new Worm();
        
        
        w->setup();
        worms.push_back(w);
    }
       
   
    
    mySound.loadSound("Foyer_Fire.mp3");
   
    //ofSoundGetSpectrum(true) ;
}

//--------------------------------------------------------------
void testApp::update()
{
    if (startCount<0)return;
    spectrum = ofSoundGetSpectrum(numWorms);
    float total =0;
    for (int i=0; i<numWorms; i++) {
        
       total+= spectrum[i];
    }
    total/=20;
    
    for (int i=0; i<numWorms; i++) {
      //   if(startCount>700)worms[i]->remove =true;
        worms[i]->update(spectrum[i],total);
    }
    //if(startCount>700)mySound.setVolume(1-(float)(startCount-700)/200);
     
}

//--------------------------------------------------------------
void testApp::draw(){
    
    if (startCount<0)return;
    startCount++;
    if (startCount<10)return;
	glEnable(GL_DEPTH_TEST);
    
    //cam.setDistance(1400); 
        
    float step =(float)(startCount-2000)/500;
    float dist = 2300-startCount*2;
    if(dist<800)dist=800;
    cam.begin();
    cam.setPosition(sinf(step)*dist ,0 ,cosf(step)*dist);
    cam.lookAt(ofVec3f(0,0,0));
    
    glEnable (GL_FOG); //enable the fog
    glFogf (GL_FOG_START, 2000);
    
    glFogf (GL_FOG_END, 3000);
 
    glFogi (GL_FOG_MODE, GL_EXP2); //set the fog mode to GL_EXP2
    GLfloat fogColor[4] = {0.01, 0.01, 0.01, 1};
    glFogfv (GL_FOG_COLOR, fogColor); //set the fog color to
    
    
    glFogf (GL_FOG_DENSITY, 0.001); //set the density to the
   // if(startCount>300)glFogf (GL_FOG_DENSITY, (100-(float)(startCount-300))/100000);
    
    glHint (GL_FOG_HINT, GL_NICEST);
   
       ofEnableLighting();
    light.enable();
    ofVec3f campos = cam.getGlobalPosition();
    campos.x +=1000;
    campos.y +=1000;
    light.setPosition( campos  );
    
    for (int i=0; i<numWorms; i++) {
        
        worms[i]->draw ();
    }
    cam.end();
    
    
    cout << "\n" << ofGetFrameRate()<< " "<< startCount;
    
   // cout <<" \n";
    /*
    ofSetHexColor(0xffffff);
	TO.draw();

    string str = "I am a the main opengl thread.\nmy current count is: ";
	str += ofToString(mainAppsCount);
    ofDrawBitmapString(str, 350, 56);


    ofSetHexColor(0xff0033);

    ofDrawBitmapString("press 's' to stop the thread and 'a' to start it", 50, 160);
    */
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){

    
    
    if (key == 'a'){
         mySound.play();
        startCount=0;
    } else if (key == 's'){
        
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}