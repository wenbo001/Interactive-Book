# Interactive Book

OpenFrameworks application that makes physical books interactive using OCR (Optical Character Recognition). The application checks for certain strings in a text. The idea is that you scan in the title of the chapter which will bring up extra information like a short movie, audio, webpage or an image.

This project is a collaboration with Wenbo Liu for the United Nations in Geneva. 

## Development:

In the Development folder you can find the most recent unstable release. In the root folder of the project you can find the most recent stable release.

## Usage:

You can add/modify what images, video or webpages you would like to show based on specific strings in the XML file located at ``/bin/data/mySettings.xml``.

## Dependencies:

**NOTE:** Currently only works on OSX.

- OpenFrameworks
- ofxGui
- ofxOpenCv
- ofxXmlSettings
- ofxTesseract

## To do:

- Add comments where necessary
- Implement smile detection (ofxSmile)
- Find a way to override the "system() is not a function issue", maybe find a different way or include a specific C++ library?
- Do more research on Regex (mid sentence, merged words)
- find a way to open the browser cross platform (iPad, Windows).
- Do more testing on other platforms. I wasn’t able to get Tesseract running properly on Windows (I didn’t try hard though).
- Add more options for user interaction: keyboard, mouse, gestures.
- Implement the possibilty of adding multiple versions of the same work like: "BASISBOEK WISKUNDE" and "BASISBOEKWISKUNDE" to increase the chance of success.
