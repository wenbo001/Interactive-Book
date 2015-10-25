//DONE
//add play movie when finding text
//load xml text as a detect text
//basic regex
//added webpage
//static image
//capital letters, spaces in between letters-> option1: match case insensetive & remove space of webcam reading
//option2: reaplce webcam reading with all lowercase, make xml data all lowercase& remove space// choose option2, because option1: the case insensetive is just half worked
//sans-serif/serif/italic all work fine, problems with some fonts having uppercase letters in lowercase typeset
//find a way how to use system(open url) from XML
//Big blobs of text really drop the framerate, maybe limit at 20 characters (ocrStr)

//TO DO
//add comments where necessary
//research XML structure/standards
//do more research on regex (mid sentence, merged words)//find a way to open the browser cross platform (iPad?, Windows)
//Make 5 different short video's (chapter 1 - 5)
//User won't know what to scan (fix with big title on nearly empty page?, recommendation)
//documentation:doxygn

//add other things when finding text (movie/webpage/image/audio/etc..)

//add user interaction motion,keyboard,mouse,touchboard?
//replace mousePressed with other user interaction (openCV/gesture?), smiles?

//OPTIONAL
//add cover interaction

#include "ofApp.h"
//regex
#include "Poco/RegularExpression.h"
using Poco::RegularExpression;

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(0);
    
    //img
    basisboekImage.loadImage("a.jpg");
    
    //video
    chapterOne.loadMovie("chapterOne.mp4");
    chapterTwo.loadMovie("chapterTwo.mp4");
    
    //xml
    //we load our settings file
    //if it doesn't exist we print the messege
    if(XML.loadFile("mySettings.xml") ){
        message = "mySettings.xml loaded!";
        cout << message << '\n';
    }else{
        message = "unable to load mySettings.xml check data/ folder";
        cout << message << '\n';
    }
    
    XMLChapterOne = XML.getValue("Book:ChapterOne", "default text");
    XMLChapterTwo = XML.getValue("Book:ChapterTwo", "default text");
    
    
    ofSetVerticalSync(true);
    ocr.setup();
    ocr.setWhitelist("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
    
    ocr.setAccuracy(ofxTesseract::ACCURATE);
    ocr.setMode(ofxTesseract::AUTO);
    
    w = 640;
    h = 480;
    
    camera.initGrabber(w, h, true);
    rgb.allocate(w, h);
}

//--------------------------------------------------------------
void ofApp::update(){
    chapterOne.update();
    
    chapterTwo.update();
    
    if(detectedText == false){
        camera.update();
        
        if (camera.isFrameNew()) {
            //copy webcam pixels to rgb image
            rgb.setFromPixels(camera.getPixels(), w, h);
            
            if(ofGetFrameNum()%30==0) { //run every 30th frame
                image.setFromPixels(camera.getPixels(), w, h, OF_IMAGE_COLOR, true);
                ocrStr = ocr.findText(image);
                //cout << ocrStr;
                //Remove the spaces of the ocrStr
                //ocrStr.erase(std::remove(ocrStr.begin(), ocrStr.end(), ' '), ocrStr.end());
                //Transform ocrStr to lower case
                //std::transform(ocrStr.begin(), ocrStr.end(), ocrStr.begin(), ::tolower);
                
                if(ocrStr.length() > 50) {
                    camera.update();
                    ocrStr.erase();
                }

                cout << ocrStr;
                Poco::RegularExpression::Match theMatch;
                // chapterOne
                Poco::RegularExpression chapterOneRE(XMLChapterOne);
                chapterOneMatch = chapterOneRE.match(ocrStr, theMatch);
                if (chapterOneMatch) {
                    detectedText = true;
                    chapterOneSrc = true;
                    //webPage = true;
                    std::cout << "found it" << '\n';
                }else {
                    std::cout << "did not find it" << '\n';
                }
                
                // chapterTwo
                Poco::RegularExpression chapterTwoRE(XMLChapterTwo);
                chapterTwoMatch = chapterTwoRE.match(ocrStr, theMatch);
                if (chapterTwoMatch) {
                    detectedText = true;
                    chapterTwoSrc = true;
                    std::cout << "found it" << '\n';
                }else {
                    std::cout << "did not find it" << '\n';
                }
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255,255,255);
    
    rgb.draw(0,0);
    
//    if(detectedText == true && basisboek == true){
//        basisboekImage.draw(0, 0, ofGetWidth(), ofGetHeight());
//    }
    
//    if(detectedText == true && chapterOneSrc == true && webPage == true){
//        system("open http://www.apple.com");
//        webPage = false;
//    }
    
    if(detectedText == true && chapterOneSrc == true){
        chapterOne.draw(0, 0, ofGetWidth(), ofGetHeight());
        chapterOne.play();
    }else {
        chapterOne.stop();
    }

    if(detectedText == true && chapterTwoSrc == true){
        chapterTwo.draw(0, 0, ofGetWidth(), ofGetHeight());
        chapterTwo.play();
    }else {
        chapterTwo.stop();
    }

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    detectedText = false;
    chapterOneSrc = false;
    chapterTwoSrc = false;
}