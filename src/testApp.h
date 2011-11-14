#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"

#include "ofxTuioClient.h"
#include "ofxMultiTouch.h"
#include "ofxMarkerHandler.h"
#include "myMtButton.h"
#include "myMtEventButton.h"
#include "myMarkerButton.h"

#include "ofxMtActionsHub.h"
#include "myMtRotatableScalableItem.h"
#include "myMtSlider.h"

class testApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	
	//TUIO CALLBACK FUNCTIONS
	void tuioObjectAdded(TuioObject & tobj);
	void tuioObjectUpdated(TuioObject & tobj);
	void tuioObjectRemoved(TuioObject & tobj);
	
	void tuioCursorAdded(TuioCursor & tcur);
	void tuioCursorRemoved(TuioCursor & tcur);
	void tuioCursorUpdated(TuioCursor & tcur);
	
	//TUIO CLIENT
	ofxTuioClient myTuio;
	
	//button without callback function
	myMtButton button;
	//button with a callback in testApp (void buttonTwoCallback())
	myMtEventButton buttonTwo;
	
	//markerButton
	myMarkerButton markerButton;
	
	//MultiTouch Actions Hub [manage priorities and zIndex/depth in the stack of each mtActionObj]
	ofxMtActionsHub mtActionsHub;
	
	//rotatable and scalable item
	myMtRotatableScalableItem draggableRotatableScalableItem;
	myMtRotatableScalableItem scalableItem;
	myMtRotatableScalableItem draggableItem;
	
	//sliders
	ofxMtActionsHub mtSliderHub;
	bool drawSliders;
	int sliderW;
	int sliderH;
	int gapW;
	myMtSlider rSlider;
	myMtSlider gSlider;
	myMtSlider bSlider;
	
	//buttonTwo Callback
	void buttonTwoCallback(ofEventArgs & voidArgs);
	void updateBackgroundColor(ofEventArgs & voidArgs);
};

#endif
