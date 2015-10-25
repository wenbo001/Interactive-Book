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
    ofImage image;
    ofImage basisboekImage;
    ofImage bauhausboekImage;
    
    //webcam
    ofVideoGrabber camera;
    ofxCvColorImage rgb;
    int w,h;
    
    //videoplayer
    ofVideoPlayer chapterOne;
    ofVideoPlayer chapterTwo;
    
    //xmlsetting
    ofxXmlSettings XML;
    string message;
    string XMLChapterOne;
    string XMLChapterTwo;
    
    //regex
    bool chapterOneMatch;
    bool chapterTwoMatch;
    
    //booleans
    bool detectedText = false;
    
    bool chapterOneSrc = false;
    bool chapterTwoSrc = false;
    
    //bool webPage = false;
};

#endif