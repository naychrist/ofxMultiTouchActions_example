#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0, 0, 0);
	ofSetVerticalSync(true);
    ofEnableDataPath();
	
	//Connect to Port
	myTuio.connect(3333);
	
	//init buttons
	//button.setSize(100, 100);
	//button.registerForMultitouchEvents();
	buttonTwo.setPos(ofGetWidth() - 230, 0);
	buttonTwo.setSize(50, 50);
	buttonTwo.registerForMultitouchEvents();
	
	/*
	markerButton.setPos(600,500);
	markerButton.setSize(60,60);
	markerButton.registerForMarkerEvents();
	*/
	
	//----------------
	//Draggable Rotate Scalable Object
	//rotatableScalableItem.setSize(100, 100);
	draggableRotatableScalableItem.setPos(ofGetWidth()/2, ofGetHeight()/2);
	draggableRotatableScalableItem.setColor(0x00FF00);
	draggableRotatableScalableItem.setPriorityLevel(1);
	
	int *tRange = new int[2];
	tRange[0] = 2;
	tRange[1] = 3;
	draggableRotatableScalableItem.setIsRotatable(true, tRange, 2);
	delete [] tRange;
	
	/*
	tRange = new int[1];
	tRange[0] = 2;
	draggableRotatableScalableItem.setIsScalable(true, tRange, 1);
	delete [] tRange;
	*/
	
	tRange = new int[2];
	tRange[0] = 1;
	tRange[1] = -4; //a negative value means the value and up. Is this case 4+
	draggableRotatableScalableItem.setIsDraggable(true, tRange, 2);
	delete [] tRange;
	//----------------
	
	//----------------
	//Scalable Object
	scalableItem.setPos(ofRandom(10, ofGetWidth()-10), ofRandom(10, ofGetHeight()-10));
	scalableItem.setColor(0xFF0000);
	scalableItem.setPriorityLevel(2);
	
	tRange = new int[2];
	tRange[0] = 2;
	tRange[1] = 3;
	scalableItem.setIsScalable(true, tRange, 2);
	delete [] tRange;
	
	tRange = new int[1];
	tRange[0] = 1;
	scalableItem.setIsDraggable(true, tRange, 1);
	delete [] tRange;
	//----------------
	
	//----------------
	//Draggable Object
	draggableItem.setPos(ofRandom(10, ofGetWidth()-10), ofRandom(10, ofGetHeight()-10));
	draggableItem.setColor(0x2233FF);
	draggableItem.setPriorityLevel(1);
	
	tRange = new int[1];
	tRange[0] = 1;
	draggableItem.setIsDraggable(true, tRange, 1);
	delete [] tRange;
	//----------------
	
	//----------------
	sliderW = 40;
	sliderH = 70;
	gapW = 15;
	drawSliders = true;
	//Slider Object - Red
	rSlider.setPos(ofGetWidth() - 3*(sliderW+gapW), ofGetHeight() - sliderH);
	rSlider.setSize(sliderW, sliderH);
	rSlider.setColor(255, 0, 0);
	rSlider.setPriorityLevel(3);
	rSlider.registerForMultitouchEvents();
	
	tRange = new int[1];
	tRange[0] = 1;
	rSlider.setIsDraggable(true, tRange, 1, false, true);
	delete [] tRange;
	
	//Slider Object - Green
	gSlider.setPos(ofGetWidth() - 2*(sliderW+gapW), ofGetHeight() - sliderH);
	gSlider.setSize(sliderW, sliderH);
	gSlider.setColor(0, 255, 0);
	gSlider.setPriorityLevel(3);
	gSlider.registerForMultitouchEvents();
	
	tRange = new int[1];
	tRange[0] = 1;
	gSlider.setIsDraggable(true, tRange, 1, false, true);
	delete [] tRange;
	
	//Slider Object - Blue
	bSlider.setPos(ofGetWidth() - 1*(sliderW+gapW), ofGetHeight() - sliderH);
	bSlider.setSize(sliderW, sliderH);
	bSlider.setColor(0, 0, 255);
	bSlider.setPriorityLevel(3);
	bSlider.registerForMultitouchEvents();
	
	tRange = new int[1];
	tRange[0] = 1;
	bSlider.setIsDraggable(true, tRange, 1, false, true);
	delete [] tRange;
	//----------------
	
	
	mtActionsHub.addObject(&draggableRotatableScalableItem);
	mtActionsHub.addObject(&scalableItem);
	mtActionsHub.addObject(&draggableItem);
	
	mtSliderHub.addObject(&rSlider);
	mtSliderHub.addObject(&gSlider);
	mtSliderHub.addObject(&bSlider);
	
	
	ofAddListener(rSlider.eMultiTouchMoved,this,&testApp::updateBackgroundColor);
	ofAddListener(gSlider.eMultiTouchMoved,this,&testApp::updateBackgroundColor);
	ofAddListener(bSlider.eMultiTouchMoved,this,&testApp::updateBackgroundColor);
	
	//add button event listener for global callback function in testApp
	ofAddListener(buttonTwo.eMultiTouchUp,this,&testApp::buttonTwoCallback);
	
	//Assign Global TUIO Callback Functions
	ofAddListener(myTuio.objectAdded,this,&testApp::tuioObjectAdded);
	ofAddListener(myTuio.objectRemoved,this,&testApp::tuioObjectRemoved);
	ofAddListener(myTuio.objectUpdated,this,&testApp::tuioObjectUpdated);
	ofAddListener(myTuio.cursorAdded,this,&testApp::tuioCursorAdded);
	ofAddListener(myTuio.cursorRemoved,this,&testApp::tuioCursorRemoved);
	ofAddListener(myTuio.cursorUpdated,this,&testApp::tuioCursorUpdated);

}

//--------------------------------------------------------------
void testApp::update(){
	//Render the items/objects using the hub
	mtActionsHub.update();
	
	//Sliders
	if (drawSliders) {
		mtSliderHub.update();
	}

}

//--------------------------------------------------------------
void testApp::draw(){
	//Render the items/objects using the hub's stack
	ofEnableAlphaBlending();
	
	glBlendFunc(GL_SRC_COLOR, GL_ONE);
	mtActionsHub.renderAsStack();
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Sliders
	if (drawSliders) {
		ofSetColor(255, 255, 255, 100);
		ofRect(ofGetWidth() - 3*(sliderW+gapW), 0, sliderW, ofGetHeight());
		ofRect(ofGetWidth() - 2*(sliderW+gapW), 0, sliderW, ofGetHeight());
		ofRect(ofGetWidth() - 1*(sliderW+gapW), 0, sliderW, ofGetHeight());
		
		mtSliderHub.renderAsStack();
	}
	
	//render the three example buttons
    //button.render();
	buttonTwo.render();
	//markerButton.render();
	
	//render TUIO Cursors and Objects
	//myTuio.drawCursors();
	//myTuio.drawObjects();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	ofToggleFullscreen();

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

void testApp::tuioObjectAdded(TuioObject & tobj){
/*	cout << " object added: " + ofToString(tobj.getSymbolID())+
	" X: "+ofToString(tobj.getX())+
	" Y: "+ofToString(tobj.getY())+
	" angle: "+ofToString(tobj.getAngleDegrees())
	<< endl;*/
	
	//forward the marker events to ofxMarker for the InteractiveObjects
	ofxMarker.markerDown(tobj.getSymbolID(), tobj.getX(), tobj.getY(), tobj.getAngleDegrees());
}

void testApp::tuioObjectRemoved(TuioObject & tobj){
/*	cout << " object removed: " + ofToString(tobj.getSymbolID())+
	" X: "+ofToString(tobj.getX())+
	" Y: "+ofToString(tobj.getY())+
	" angle: "+ofToString(tobj.getAngleDegrees())
	<< endl;*/
	
	//forward the marker events to ofxMarker for the InteractiveObjects
	ofxMarker.markerUp(tobj.getSymbolID(), tobj.getX(), tobj.getY(), tobj.getAngleDegrees());
}

void testApp::tuioObjectUpdated(TuioObject & tobj){
	/*cout << " object updated: " + ofToString(tobj.getSymbolID())+
	" X: "+ofToString(tobj.getX())+
	" Y: "+ofToString(tobj.getY())+
	" angle: "+ofToString(tobj.getAngleDegrees())
	<< endl;*/
	
	//forward the marker events to ofxMarker for the InteractiveObjects
	ofxMarker.markerMoved(tobj.getSymbolID(), tobj.getX(), tobj.getY(), tobj.getAngleDegrees());
}

void testApp::tuioCursorAdded(TuioCursor & tcur){
	/*cout << " cursor added: " + ofToString(tcur.getCursorID())+
	" X: "+ofToString(tcur.getX())+
	" Y: "+ofToString(tcur.getY())
	<< endl;*/
	
	ofxMultiTouchCustomDataSF multiTouchCustomData;
	multiTouchCustomData.sessionID = tcur.getSessionID();
	
	mtActionsHub.touchDown(tcur.getX(), tcur.getY(), tcur.getCursorID(), &multiTouchCustomData);
	mtSliderHub.touchDown(tcur.getX(), tcur.getY(), tcur.getCursorID(), &multiTouchCustomData);
	
	/*
	draggableRotatableScalableItem.touchDown(tcur.getX(), tcur.getY(), tcur.getCursorID(), &multiTouchCustomData);
	if(draggableRotatableScalableItem.ownTouchCursor(tcur.getSessionID())) {
		return;
	}
	*/
	
	//forward the touch events to ofxMultiTouch for the InteractiveObjects
	ofxMultiTouch.touchDown(tcur.getX(), tcur.getY(), tcur.getCursorID(), &multiTouchCustomData);
}

void testApp::tuioCursorRemoved(TuioCursor & tcur){
	/*cout << " cursor removed: " + ofToString(tcur.getCursorID())+
	 " X: "+ofToString(tcur.getX())+
	 " Y: "+ofToString(tcur.getY())
	 << endl;*/
	
	mtActionsHub.touchUp(tcur.getX(), tcur.getY(), tcur.getCursorID(), NULL);
	mtSliderHub.touchUp(tcur.getX(), tcur.getY(), tcur.getCursorID(), NULL);
	
	//draggableRotatableScalableItem.touchUp(tcur.getX(), tcur.getY(), tcur.getCursorID(), NULL);

	//forward the touch events to ofxMultiTouch for the InteractiveObjects
	ofxMultiTouch.touchUp(tcur.getX(), tcur.getY(), tcur.getCursorID(), NULL);
}

void testApp::tuioCursorUpdated(TuioCursor & tcur){
	/*cout << " cursor updated: " + ofToString(tcur.getCursorID())+
	 " X: "+ofToString(tcur.getXSpeed())+
	 " Y: "+ofToString(tcur.getYSpeed())
	 << endl;*/
	
	ofxMultiTouchCustomDataSF multiTouchCustomData;
	multiTouchCustomData.sessionID = tcur.getSessionID();
	
	mtActionsHub.touchMoved(tcur.getX(), tcur.getY(), tcur.getCursorID(), &multiTouchCustomData);
	mtSliderHub.touchMoved(tcur.getX(), tcur.getY(), tcur.getCursorID(), &multiTouchCustomData);
	/*
	draggableRotatableScalableItem.touchMoved(tcur.getX(), tcur.getY(), tcur.getCursorID(), NULL);
	if(draggableRotatableScalableItem.ownTouchCursor(tcur.getSessionID())) {
		return;
	}
	*/
	//forward the touch events to ofxMultiTouch for the InteractiveObjects
	ofxMultiTouch.touchMoved(tcur.getX(), tcur.getY(), tcur.getCursorID(), NULL);
}

//button Two Callback
void testApp::buttonTwoCallback(ofEventArgs & voidArgs){
	drawSliders = !drawSliders;
}

void testApp::updateBackgroundColor(ofEventArgs & voidArgs){
	
	int rLevel = 255 - (rSlider.y/ofGetHeight()) * 255;
	int gLevel = 255 - (gSlider.y/ofGetHeight()) * 255;
	int bLevel = 255 - (bSlider.y/ofGetHeight()) * 255;
	
	rSlider.setColor(rLevel, 0, 0);
	gSlider.setColor(0, gLevel, 0);
	bSlider.setColor(0, 0, bLevel);
	
	cout << (bSlider.y/ofGetHeight()) << " ++ " << rLevel << " -- " << gLevel << " __ " << bLevel << "\n";
	
	ofBackground(rLevel, gLevel, bLevel);
}


