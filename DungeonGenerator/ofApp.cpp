#include "ofApp.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>


int * createmap(int * map, int n, int size);

void drawtile(int color);

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(3);
	ofEnableDepthTest();


	srand(time(NULL));
	std::cout << "grandezza max 50";
	std::cout << "\n";
	std::cin >> n;
	p = createmap(p, n, size);
}

int * createmap (int * map, int n,int size) {
	bool first = true;
	int roomheight = 0;
	int roomwidth = 0;
	for (int i = 0; i < n*n; i++)
	{
		map[i] = 0;
	}
	for (int i = 0; i < n*n; i++)
	{
		if (i<n || i>n*roomheight)
		{
			int r = rand() % 100 + 1;
			if (r < 10)
			{
				roomheight = rand() % n/size +2;
				roomwidth = rand() % n/size + 2;
				for (int j = 0; j < roomheight; j++)
				{
					for (int c = 0; c < roomwidth; c++)
					{
						map[i + n * j + c] = 1;
					}
				}
			}
		}

		if (i<n || i>n*(n - 1) || i % n == 0 || (i+1) % n == 0)
		{
			map[i] = 0;
		}
	}
	return map;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//---------------------------------------------------------------
void ofApp::draw(){
	ofDrawBitmapStringHighlight("comandi: A aumenta l'ampiezza, S diminuisce l'ampiezza", ofVec3f(10, 10));
	ofDrawBitmapStringHighlight("G rigenera il dungeon", ofVec3f(10, 40));
	ofDrawBitmapStringHighlight("Ampiezza =" + ofToString(size), ofVec3f(10, 70));

	ofTranslate(ofGetWidth() * 0.5 +n*10, ofGetHeight() * 0.5 +n*10);


	//cam.begin();

	for (int i = 0; i < n*n; i++)
	{
		if (p[i] == 1 && i%n!=0)
		{
			ofTranslate(20, 0);
			ofPushMatrix();
			drawtile(2); //2 = colore tile bianche
			ofPopMatrix();

		}
		else if (i%n == 0 && p[i]==1)
		{
			ofTranslate(-20*(n-1), -20);

			ofPushMatrix();
			drawtile(2);
			ofPopMatrix();
		}
		else if (i%n == 0)
		{
			ofTranslate(-20 * (n - 1), -20);

			ofPushMatrix();
			drawtile(1);
			ofPopMatrix();
		}
		else
		{
			ofTranslate(20, 0);

			ofPushMatrix();
			drawtile(1);
			ofPopMatrix();
		}
	}

	//cam.end();
}


void drawtile(int color)
{

	ofFill();
	ofSetColor(color*100 + 39);
	ofBeginShape();
	ofVertex(glm::vec2(-9, -10));
	ofVertex(glm::vec2(9, -10));
	ofVertex(glm::vec2(9, 10));
	ofVertex(glm::vec2(-9, 10));
	ofEndShape(true);

	ofNoFill();
	ofSetColor(39);
	ofBeginShape();
	ofVertex(glm::vec2(-10, -10));
	ofVertex(glm::vec2(10, -10));
	ofVertex(glm::vec2(10, 10));
	ofVertex(glm::vec2(-10, 10));
	ofEndShape(true);

}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case 'g':
		p = createmap(p, n, size);
		break;
	case 's':
		size++;
		break;
	case 'a':
		if (size > 1)
		{
			size--;
		}
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
