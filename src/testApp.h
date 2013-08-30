#pragma once

#include "ofMain.h"
#include "ofxSyphon.h"

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
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void setupArduino(const int & version);
    void exit();
    void on(int pin);
    void videoEvent(float seconds);
		void off();

		bool bArduinoConnecting;
		bool bArduinoReady;
		float duration;
		float currentSecond;
		int currentFan;

		ofArduino arduino;
		ofVideoPlayer video;
		ofTexture texture;

		ofxSyphonServer server;
		
};
