#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofAddListener(tuio.objectAdded,this,&testApp::objectAdded);
	ofAddListener(tuio.objectRemoved,this,&testApp::objectRemoved);
	ofAddListener(tuio.objectUpdated,this,&testApp::objectUpdated);
	ofAddListener(tuio.cursorAdded,this,&testApp::tuioAdded);
	ofAddListener(tuio.cursorRemoved,this,&testApp::tuioRemoved);
	ofAddListener(tuio.cursorUpdated,this,&testApp::tuioUpdated);

	ofSetFrameRate(60);
	tuio.start(3333);
}

//--------------------------------------------------------------
void testApp::update(){
	tuio.getMessage();
}


//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(0,0,0);
	tuio.drawCursors();
	tuio.drawObjects();
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){

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
void testApp::mouseReleased(){
}


void testApp::objectAdded(ofxTuioObject & tuioObject){
	cout << " new object: " + ofToString(tuioObject.getFiducialId())+
		" X: "+ofToString(tuioObject.getX())+
		" Y: "+ofToString(tuioObject.getY())+
		" angle: "+ofToString(tuioObject.getAngleDegrees())
	<< endl;
}
void testApp::objectRemoved(ofxTuioObject & tuioObject){
	cout << " object removed: " + ofToString(tuioObject.getFiducialId())+
		" X: "+ofToString(tuioObject.getX())+
		" Y: "+ofToString(tuioObject.getY())+
		" angle: "+ofToString(tuioObject.getAngleDegrees())
	<< endl;
}
void testApp::objectUpdated(ofxTuioObject & tuioObject){
	cout << " object updated: " + ofToString(tuioObject.getFiducialId())+
		" X: "+ofToString(tuioObject.getX())+
		" Y: "+ofToString(tuioObject.getY())+
		" angle: "+ofToString(tuioObject.getAngleDegrees())
	<< endl;
}

void testApp::tuioAdded(ofxTuioCursor & tuioCursor){
	cout << " new cursor: " + ofToString(tuioCursor.getFingerId())+
		" X: "+ofToString(tuioCursor.getX())+
		" Y: "+ofToString(tuioCursor.getY())
	<< endl;
}
void testApp::tuioRemoved(ofxTuioCursor & tuioCursor){
	cout << " cursor removed: " + ofToString(tuioCursor.getFingerId())+
		" X: "+ofToString(tuioCursor.getX())+
		" Y: "+ofToString(tuioCursor.getY())
	<< endl;
}
void testApp::tuioUpdated(ofxTuioCursor & tuioCursor){
	cout << " cursor updated: " + ofToString(tuioCursor.getFingerId())+
		" X: "+ofToString(tuioCursor.getX())+
		" Y: "+ofToString(tuioCursor.getY())
	<< endl;
}
