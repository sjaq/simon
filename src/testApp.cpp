#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
  ofSetVerticalSync(true);
  ofSetFrameRate(30);
  ofBackground(255, 0, 0);
  ofSetLogLevel(OF_LOG_VERBOSE);

  bArduinoConnecting = false;
  bArduinoReady = false;
  currentSecond = 0.0;
  currentFan = 0;

  video.setUseTexture(false);
  video.setPixelFormat(OF_PIXELS_RGBA);
  video.setLoopState(OF_LOOP_NONE);
  video.loadMovie("video.mov");
  
  texture.allocate(video.getWidth(), video.getHeight(), GL_RGBA);

  server.setName("Video Output");
}

void testApp::setupArduino(const int & version) {
  ofRemoveListener(arduino.EInitialized, this, &testApp::setupArduino);
  
  arduino.sendDigitalPinMode(2, ARD_OUTPUT);
   arduino.sendDigitalPinMode(3, ARD_OUTPUT);
   arduino.sendDigitalPinMode(4, ARD_OUTPUT);  
  
  bArduinoReady = true;
  if(bArduinoReady) {
    video.play();
  }
}

//--------------------------------------------------------------
void testApp::update(){
  arduino.update();
  video.update();
    
  if(video.isLoaded()){
    duration = video.getDuration();
  }

  if(!bArduinoConnecting) {
    bArduinoConnecting = true;
    arduino.connect("tty.usbmodemfd131", 57600);
    ofAddListener(arduino.EInitialized, this, &testApp::setupArduino);  
  } else if(bArduinoReady && video.isLoaded()) {
    this->videoEvent(video.getPosition() * duration);
  }
}

void testApp::videoEvent(float seconds){
  currentSecond = seconds;

  if(seconds > 0 && seconds < 5) {
    this->on(2);
  } else if(seconds > 5 && seconds < 10) {
    this->on(3);
  } else if(seconds > 10 && seconds < 15) {
    this->on(4);
  } else {
    this->off();
  }
    
  if(seconds > 15) {
    video.setPosition(0.0);
  }
}

//--------------------------------------------------------------
void testApp::draw(){
  if(video.isLoaded() && video.isFrameNew()) {
    texture.loadData(video.getPixels(), video.getWidth(), video.getHeight(), GL_RGBA);
    server.publishTexture(&texture);
  }

  ofSetHexColor(0xFFFFFF);

  string fps = "FPS: " + ofToString(ofGetFrameRate(), 2);
  ofDrawBitmapString(fps, 10, 20);

  string msgSecond = "Current Second: " + ofToString(currentSecond, 2);
  ofDrawBitmapString(msgSecond, 10, 35);

  string msgFan = "Current Fan: " + ofToString(currentFan, 2);
  ofDrawBitmapString(msgFan, 10, 50);
}

void testApp::exit(){
  ofLog(OF_LOG_NOTICE, "Arduino off!");

  if(bArduinoReady) {
    this->off();
  }
}

void testApp::on(int pin){
  currentFan = pin;

  if(pin == 2) {
    arduino.sendDigital(2, ARD_ON);
    arduino.sendDigital(3, ARD_OFF);
    arduino.sendDigital(4, ARD_OFF);
  } else if(pin == 3) {
    arduino.sendDigital(2, ARD_OFF);
    arduino.sendDigital(3, ARD_ON);
    arduino.sendDigital(4, ARD_OFF);
  } else if(pin == 4) {
    arduino.sendDigital(2, ARD_OFF);
    arduino.sendDigital(3, ARD_OFF);
    arduino.sendDigital(4, ARD_ON);
  }
}

void testApp::off() {
  arduino.sendDigital(2, ARD_OFF);
  arduino.sendDigital(3, ARD_OFF);
  arduino.sendDigital(4, ARD_OFF);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
  switch(key) {
    case 'f':
      ofToggleFullscreen();
      break;
    case 'p':
      if(video.getPosition() == 1.0) { 
        video.setPosition(0.0);
        video.play();
      } else if(video.isPaused()) {
        video.play();
      } else {
        video.setPaused(true);
      }
      break;
    case '1':
      video.setPosition(0.1);
      break;
    case '2':
      video.setPosition(0.2);
      break;
    case '3':
      video.setPosition(0.3);
      break;
    case '4':
      video.setPosition(0.4);
      break;
    case '5':
      video.setPosition(0.5);
      break;
    case '6':
      video.setPosition(0.6);
      break;
    case '7':
      video.setPosition(0.7);
      break;
    case '8':
      video.setPosition(0.8);
      break;
    case '9':
      video.setPosition(0.9);
      break;
    case '0':
      video.setPosition(0.0);
      break;
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