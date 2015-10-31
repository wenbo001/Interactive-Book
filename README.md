# Interactive Book

OpenFrameworks application that makes physical books interactive using OCR (Optical Character Recognition). The application checks for certain strings in a text. The idea is that you scan in the title of the chapter which will bring up extra information like a short movie, audio, webpage or an image.

This project is a collaboration with Wenbo Liu for the United Nations in Geneva. 

## Development:

In the Development folder you can find the most recent unstable release.

## Usage:

You can add/modify what images, video or webpages you would like to show based on specific strings in the XML file located ``/bin/data/mySettings.xml``.  

## Dependencies:

**NOTE:** Currently only works on OSX.

- OpenFrameworks
- ofxGui
- ofxOpenCv
- ofxXmlSettings
- ofxTesseract
