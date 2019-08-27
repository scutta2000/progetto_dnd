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

	x = y = 0;
	z = 200;

	cam.setPosition(x, y, z);


	srand(time(NULL));
	std::cout << "grandezza max 50";
	std::cout << "\n";
	std::cin >> n;
	p = createmap(p, n, size);
}


int * createmap (int * map, int n,int size) {
	bool stop = true;
	bool continua = true;
	bool orizzontale = false;
	bool verticale = false;
	int roomheight = 0;
	int roomwidth = 0;
	float lastcoordx = rand() % n + 1;
	float lastcoordy = rand() % n + 1;
	float coordx = 1;
	float coordy = 1;
	int	puntox = 1;
	int puntoy = 1;
	float m = 0;
	int q;
	int jmaint;
	int xmin;
	int ymin;
	int diffx=0;
	int diffy=0;
	float nquadretti = 0;
	float risultato = 1;


	for (int i = 0; i < n*n; i++)
	{
		map[i] = 0;
	}
	for (int i = 0; i < n*n; i++)
	{
		if (i < n*roomheight || i>n*roomheight) // (i < n || i>n*roomheight)
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

				int r = rand() % 100 + 1;
				stop = false;

				coordx = i - ((i / n)*(n));
				coordy = i / n + 1;


				verticale = false;

				if (coordx == lastcoordx)
				{
					verticale = true;
				}
				else
				{
					m = (lastcoordy - coordy) / (lastcoordx - coordx);
					bool continua = true;
					if (m > 0)
					{
						if (m < 1)
						{
							for (float j = 1; j <= n / 2 && continua; j++)
							{
								risultato = risultato / j;
								if (risultato < m)
								{
									nquadretti = j;
									continua = false;
								}
							}
						}
						else
						{
							nquadretti = floor(m);
						}
					}
					else if(m<0)
					{
						if (m > -1)
						{
							risultato = risultato * -1;
							for (float j = 1; j <= n / 2 && continua; j++)
							{
								risultato = risultato / j;
								if (risultato > m)
								{
									nquadretti = j;
									continua = false;
								}
							}
						}
						else
						{
							nquadretti = ceil(m);
						}
					}
				}

				orizzontale = false;

				if (m == 0)
				{
					orizzontale = true;
				}

				q = lastcoordy - m * lastcoordx;

				std::cout << "\n" << "-----------------------" << "\n";
				std::cout << "m =" << m << "\n";
				std::cout << "q =" << q << "\n";
				std::cout << "verticale =" << verticale << "\n";
				std::cout << "orizzontale =" << orizzontale << "\n";
				std::cout << "Punto 1, x = " << lastcoordx << " y = " << lastcoordy << "\n";
				std::cout << "Punto 2, x = " << coordx << " y = " << coordy << "\n";

				stop = false;

				if (coordx > lastcoordx)
				{
					xmin = lastcoordx ;
					diffx = coordx - lastcoordx ;
					std::cout << "lunghezza x =" << diffx << "\n";
				}
				else
				{
					xmin = coordx ;
					diffx = lastcoordx - coordx ;
					std::cout << "lunghezza x =" << diffx << "\n";
				}


				if (coordy > lastcoordy && verticale)
				{
					ymin = lastcoordy;
					diffy = coordy - lastcoordy ;
					std::cout << "lunghezza y =" << diffy << "\n";
				}
				else if(coordy <= lastcoordy && verticale)
				{
					ymin = coordy;
					diffy = lastcoordy - coordy ;
					std::cout << "lunghezza y =" << diffy << "\n";
				}

				std::cout << "-----------------------" << "\n";



				if (!verticale)
				{
					for (float j = 1; j <= diffx && !stop; j = j++)
					{

						puntoy = m * (j+xmin) + q;
						jmaint = j;

						int nquadrettimaint = nquadretti;

						if ((puntoy - 1 + nquadretti) * n + j + xmin < n*n && (puntoy - 1 + nquadretti) * n + j + xmin >0)
						{
							if (map[(puntoy - 1 + nquadrettimaint) * n + jmaint + xmin] == 2)
							{
								stop = true;
								std::cout << "STOP" << "\n";
							}
							else
							{
								for (int x = 0; x <= nquadretti; x++)
								{
									map[(puntoy - 1 + nquadrettimaint + x) * n + jmaint + xmin] = 2;
									std::cout << (puntoy - 1 + nquadrettimaint) * n + j + xmin << " ";
								}

							}
						}
					}
				}
				else
				{
					for (float j = 1; j <= diffy && !stop; j = j++)
					{
						jmaint = j;
						if (i - n * (jmaint + ymin) < n*n && i - n * (jmaint + ymin) > 0)
						{
							if(map[i - n * (jmaint + ymin)] == 2)
							{
								stop = true;
								std::cout << "STOP" << "\n";
							}
							else
							{
								map[i - n * (jmaint + ymin)] = 2;
								std::cout << i - n * (jmaint + ymin) << " ";
							}
						}
					}
				}

				lastcoordy = i / n + 1;
				lastcoordx = i - ((i / n)*(n));
				
			}
		}

		if (i<n || i>n*(n - 1) || i % n == 0 || (i+1) % n == 0)
		{
			map[i] = 0;
		}
	}

	for (int i = 0; i < n*n; i++)
		if (i<n || i>n*(n - 1) || i % n == 0 || (i + 1) % n == 0)
		{
			map[i] = 0;
		}
	

	return map;
}



//--------------------------------------------------------------
void ofApp::update(){

}

//---------------------------------------------------------------
void ofApp::draw(){
	ofDrawBitmapStringHighlight("comandi: T aumenta l'ampiezza, R diminuisce l'ampiezza", ofVec3f(10, 10));
	ofDrawBitmapStringHighlight("G rigenera il dungeon", ofVec3f(10, 40));
	ofDrawBitmapStringHighlight("Ampiezza =" + ofToString(size), ofVec3f(10, 70));

	ofTranslate(ofGetWidth() * 0.5 +n*10, ofGetHeight() * 0.5 +n*10);


	cam.begin();
	cam.setPosition(x, y, z);

	for (int i = 0; i < n*n; i++)
	{
		if (p[i] == 1 && i%n!=0)
		{
			ofTranslate(20, 0);
			ofPushMatrix();
			drawtile(2); //2 = colore tile bianche
			ofPopMatrix();

		}
		else if(p[i] == 2 && i%n != 0) //tile di collegamento
		{
			ofTranslate(20, 0);
			ofPushMatrix();
			drawtile(2); 
			ofPopMatrix();
		}
		else if (i%n == 0 && p[i] == 2) //tile di collegamento
		{
			ofTranslate(-20 * (n - 1), -20);

			ofPushMatrix();
			drawtile(2);
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


	cam.end();
}


void drawtile(int color)
{

	ofFill();
	ofSetColor(color*100 + 39);
	ofBeginShape();
	ofVertex(glm::vec2(-10, -10));
	ofVertex(glm::vec2(10, -10));
	ofVertex(glm::vec2(10, 10));
	ofVertex(glm::vec2(-10, 10));
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
		std::cout << "\n" << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
		std::cout << "\n" << "-----NUOVA MAPPA-----";
		p = createmap(p, n, size);
		break;
	case 't':
		size++;
		break;
	case 'r':
		if (size > 1)
		{
			size--;
		}
		break;
	case 'w':
		y = y + 10;
		break;
	case 's':
		y = y - 10;
		break;
	case 'a':
		x = x - 10;
		break;
	case 'd':
		x = x + 10;
		break;
	case 'e':
		z = z + 10;
		break;
	case 'q':
		if (z > 10)
		{
			z = z - 10;
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
