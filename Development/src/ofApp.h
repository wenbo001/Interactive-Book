#ifndef _OF_APP
#define _OF_APP

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxTesseract.h"
#include "ofxXmlSettings.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    void mousePressed(int x, int y, int button);

    //tesseract
    ofxTesseract ocr;
    string ocrStr;

    //webcam
    ofVideoGrabber camera;
    ofxCvColorImage rgb;
    int w,h;

    //image
    ofImage exampleImage;

    //videoplayer
    ofVideoPlayer exampleVideo;

    //webpage
    bool exampleWebPage = false;

    //xmlsetting
    ofxXmlSettings XML;
    string message;
    string xmlFirstExampleString;
    string xmlSecondExampleString;
    string xmlThirdExampleString;

    //regex
    bool firstExampleStringMatch;
    bool secondExampleStringMatch;
    bool thirdExampleStringMatch;

    //booleans
    bool detectedText = false;
    bool exampleImageBoolean = false;
    bool exampleVideoBoolean = false;
};

#endif
