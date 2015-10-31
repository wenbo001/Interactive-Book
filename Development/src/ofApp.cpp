#include "ofApp.h"
#include "Poco/RegularExpression.h"
using Poco::RegularExpression;

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(0);

    if(XML.loadFile("mySettings.xml")){
        message = "mySettings.xml loaded!";
        cout << message << '\n';
    }else{
        message = "unable to load mySettings.xml check data/ folder";
        cout << message << '\n';
    }

    //strings to look for
    xmlExampleString = XML.getValue("Book:Example", "default text");

    //image
    xmlExampleImage = XML.getValue("Image:Example", "default text");
    exampleImage.loadImage(xmlExampleImage);

    //video
    xmlExampleVideo = XML.getValue("Video:Example", "default text");
    exampleVideo.loadMovie(xmlExampleVideo);

    //webpage
    xmlExampleWebpage = XML.getValue("Webpage:Example", "default text");
    exampleWebpage = system(xmlExampleWebpage);

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
    chapterOne.update(); //necessary?

    if(detectedText == false){
        camera.update();

        if (camera.isFrameNew()) {
            rgb.setFromPixels(camera.getPixels(), w, h);

            if(ofGetFrameNum()%30==0) {
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
                Poco::RegularExpression::Match matchedString;

                //firstExample
                Poco::RegularExpression firstExampleStringRE(xmlFirstExampleString);
                firstExampleStringMatch = firstExampleStringRE.match(ocrStr, matchedString);

                if (firstExampleStringMatch) {
                    detectedText = true;
                    exampleImageBoolean = true;
                    //exampleVideoBoolean = true;
                    //exampleWebPageBoolean = true;
                }

                Poco::RegularExpression secondExampleStringRE(xmlSecondExampleString);
                secondExampleStringMatch = secondExampleStringRE.match(ocrStr, matchedString);

                if (secondExampleStringMatch) {
                    detectedText = true;
                    //exampleImageBoolean = true;
                    exampleVideoBoolean = true;
                    //exampleWebPageBoolean = true;
                }

                Poco::RegularExpression thirdExampleStringRE(xmlThirdExampleString);
                thirdExampleStringMatch = thirdExampleStringRE.match(ocrStr, matchedString);

                if (thirdExampleStringMatch) {
                    detectedText = true;
                    //exampleImageBoolean = true;
                    //exampleVideoBoolean = true;
                    exampleWebPageBoolean = true;
                }
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetColor(255,255,255);

    rgb.draw(0,0);

    if(detectedText && exampleImageBoolean){
        exampleImage.draw(0, 0, ofGetWidth(), ofGetHeight());
    }

    if(detectedText && exampleVideoBoolean){
        exampleVideo.draw(0, 0, ofGetWidth(), ofGetHeight());
        exampleVideo.play();
    }else {
        exampleVideo.stop();
    }

    if(detectedText && exampleWebPageBoolean){
        exampleWebPage;
        webPageBoolean = false;
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    detectedText = false;
    exampleImageBoolean = false;
    exampleVideoBoolean = false;
}
