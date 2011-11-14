#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){

    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1680,1050, OF_FULLSCREEN);// can be OF_WINDOW or OF_FULLSCREEN
	ofSetWindowPosition(1920, 0);
	ofRunApp( new testApp());

}
