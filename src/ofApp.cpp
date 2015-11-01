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
    xmlFirstExampleString = XML.getValue("Settings:Book:firstExample", "default text");
    xmlSecondExampleString = XML.getValue("Settings:Book:secondExample", "default text");
    xmlThirdExampleString = XML.getValue("Settings:Book:thirdExample", "default text");

    //image
    xmlExampleImage = XML.getValue("Settings:Image:Example", "default text");
    exampleImage.loadImage(xmlExampleImage);

    //video
    xmlExampleVideo = XML.getValue("Settings:Video:Example", "default text");
    exampleVideo.loadMovie(xmlExampleVideo);

    //webpage
    xmlExampleWebpage = XML.getValue("Webpage:Example", "default text");
    //exampleWebPage = system(xmlExampleWebpage);

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
    exampleVideo.update(); //necessary?

    if(detectedText == false){
        camera.update();

        if (camera.isFrameNew()) {
            rgb.setFromPixels(camera.getPixels(), w, h);

            if(ofGetFrameNum()%30==0) {
                image.setFromPixels(camera.getPixels(), w, h, OF_IMAGE_COLOR, true);
                ocrStr = ocr.findText(image);

//                cout << ocrStr;
//                ocrStr.erase(std::remove(ocrStr.begin(), ocrStr.end(), ' '), ocrStr.end());
//                std::transform(ocrStr.begin(), ocrStr.end(), ocrStr.begin(), ::tolower);

//                if(ocrStr.length() > 50) {
//                    camera.update();
//                    ocrStr.erase();
//                }

                cout << ocrStr;
                Poco::RegularExpression::Match matchedString;

                //firstExample
                Poco::RegularExpression firstExampleStringRE(xmlFirstExampleString);
                firstExampleStringMatch = firstExampleStringRE.match(ocrStr, matchedString);

                if (firstExampleStringMatch) {
                    detectedText = true;
                    exampleImageBoolean = true;
                }

                Poco::RegularExpression secondExampleStringRE(xmlSecondExampleString);
                secondExampleStringMatch = secondExampleStringRE.match(ocrStr, matchedString);

                if (secondExampleStringMatch) {
                    detectedText = true;
                    exampleVideoBoolean = true;
                }

                Poco::RegularExpression thirdExampleStringRE(xmlThirdExampleString);
                thirdExampleStringMatch = thirdExampleStringRE.match(ocrStr, matchedString);

                if (thirdExampleStringMatch) {
                    detectedText = true;
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
        system("open http://www.google.com");
        exampleWebPageBoolean = false;
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    detectedText = false;
    exampleImageBoolean = false;
    exampleVideoBoolean = false;
}
