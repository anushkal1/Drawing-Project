/* ZJW simple C++ code to write out a PPM file representing shapes */

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <unordered_map>
#include "ppmR.h"
#include "color.h"
#include "rect.h"
#include "ellipse.h"
#include "polygon.h"
#include "bird.h"
#include "bird.h"

using namespace std;

/*write out PPM data, using the defined implicit equation
  interior points write a different color then exterior points */

void writeOut(ostream& out, ppmR& theWriter,
				vector<shared_ptr<ellipse>> IEs,
				vector<shared_ptr<Rect> > Rs,
				vector<shared_ptr<Polygon> > Ps) {

	float res;
	color inC;
	color drawC;
	color background(12, 34, 56);
	bool inTrue = false;
	double curDepth = -1.0;

	//for every point in the 2D space
	for (int y=0; y < theWriter.height; y++) {
		for (int x =0; x < theWriter.width; x++) {

			inTrue = false;
			curDepth = -1;
			//iterate through all possible equations (note 'front' determined by order in vector)

			for (auto eq : IEs) {
				res = eq->eval(x, y);
				if (res < 0 && eq->getDepth() > curDepth) {
					inC = eq->getInC();
					inTrue = true;
					curDepth = eq->getDepth();
				}
			}

			for (auto rect: Rs) {
				if (rect->evalIn(x, y) && rect->getDepth() > curDepth){
					inC = rect->getInC();
					inTrue = true;
					curDepth = rect->getDepth();
				}
			}

			for (auto poly:Ps) {
				if (poly->eval(x, y) && poly->getDepth() > curDepth){
					inC = poly->getInC();
					inTrue = true;
					curDepth = poly->getDepth();
				}
			}

			if (inTrue) {
				theWriter.writePixel(out, x, y, inC);
			}
			else
				theWriter.writePixel(out, x, y, background);
		}
		theWriter.writeNewLine(out);
	}
}


/*read command line arguments and write out new ascii file of given size */
int main(int argc, char *argv[]) {
	unordered_map<string, color> redBirdColors;
	redBirdColors["red"] = color(216, 0, 38);
	redBirdColors["dark red"] = color(170, 0, 30);
	redBirdColors["desert sand"] = color(227, 196, 166);

	unordered_map<std::string, color> mainColors = {
      {"black", color(0, 0, 0) },
      {"white", color(255, 255, 255) },
      {"beakColor", color(255, 175, 0)}
    };

	unordered_map<string, color> yellowBirdColors;
	yellowBirdColors["main yellow"] = color(242, 221, 0);
	yellowBirdColors["reflective yellow"] = color(250, 255, 209);
	yellowBirdColors["red"] = color(180, 53, 0);

	unordered_map<string, color> blackBirdColors;
	blackBirdColors["tinted black"] = color(68, 68, 68);
	blackBirdColors["red"] = color(198, 68, 0);

	unordered_map<string, color> birdColors;
	birdColors["green"] = color(13, 186, 22);
	birdColors["outlined green"] = color(5, 132, 12);
	birdColors["dark green"] = color(38, 115, 42);

	ofstream outFile;
	int sizeX, sizeY;

	bird redBird = bird();
	vector<shared_ptr<ellipse>> theEllipses;
	vector<shared_ptr<Rect>> theRects;
	vector<shared_ptr<Polygon>> thePolys;
	vector<color> niceC;
	niceC.push_back(color(117, 119, 186));
	niceC.push_back(color(45, 47, 135));
	niceC.push_back(color(174, 209, 238));
	niceC.push_back(color(239, 174, 115));
	niceC.push_back(color(186, 140, 117));

	if (argc < 4) {
		cerr << "Error format: a.out sizeX sizeY outfileName" << endl;
		exit(0);
	}

	string outFilename;
	sizeX = stoi(argv[1]);
	sizeY = stoi(argv[2]);
	ppmR theWriter(sizeX, sizeY);

	cout << "sizeX: " << sizeX << " sizeY: " << sizeY << endl;

	for (int j=0; j < 15; j++) {
		theEllipses.push_back(make_shared<ellipse>(vec2(nicerRand(10, sizeX-10), nicerRand(10, sizeX-10)),
								vec2(nicerRand(11, 20), nicerRand(11, 20)), nicerRand(1, 3), niceC[nicerRand(0,5)]));
	}

	for (int i=0; i < 5; i++) {
		theRects.push_back(make_shared<Rect>(vec2(nicerRand(10, sizeX-10), nicerRand(10, sizeX-10)),
				nicerRand(8, 23), nicerRand(7, 22), color(nicerRand(23, 210)), nicerRand(1, 3)));
	}

	//create a vector of vertices for the triangle
	//vertices specified counter clockwise!
	vector<vec2> triVerts;
	triVerts.push_back(vec2(100, 50));
	triVerts.push_back(vec2(150, 10));
	triVerts.push_back(vec2(205, 50));

	thePolys.push_back(make_shared<Polygon>(triVerts, 5, color(252)) );


	vector<vec2> newTriVerts;
	newTriVerts.push_back(vec2(100, 100));
	newTriVerts.push_back(vec2(200, 100));
	newTriVerts.push_back(vec2(150, 50));

	thePolys.push_back(make_shared<Polygon>(newTriVerts, 5, color(252)) );



	vector<vec2> houseVerts;
	houseVerts.push_back(vec2(100, 100));
	houseVerts.push_back(vec2(150, 60));
	houseVerts.push_back(vec2(205, 100));
	houseVerts.push_back(vec2(210, 270));
	houseVerts.push_back(vec2(105, 271));

	thePolys.push_back(make_shared<Polygon>(houseVerts, 5, niceC[0]) );

	//you will use these
	vec2 trans1(-1, 1);
	vec2 trans2(1, 1);
	vec2 trans3(-1, -1);
	vec2 accel(0, 1);

	//loop through and produce more than on image - change to 30
	for (int i=0; i < 3; i++) {

	  trans1 = trans1 + accel;
	  trans2 = trans2 + accel;
	  trans3 = trans3 + accel;

	  //set up unique filename that conforms to processign movie maker
	  outFilename.append(argv[3]);
	  if (i < 10)
		outFilename.append(to_string(0));
		outFilename.append(to_string(i));
		outFilename.append(".ppm");
		//open new file
		outFile.open(outFilename);
		if (outFile) {
		  cout << "writing an image of size: " << sizeX << " " << sizeY << " to: " << argv[3] << endl;
		  theWriter.writeHeader(outFile);
		   //uncomment when task 4 is done
		  for (auto s : theEllipses) {
		  	s->translate(trans1);
		  }
		  for (auto p : thePolys) {
		  	p->translate(trans3);
		  }
		  for (auto r : theRects) {
		  	r->translate(trans2);
		  }

		  writeOut(outFile, theWriter, theEllipses, theRects, thePolys);
		  outFile.close();
		  outFilename.erase();
		} else {
		  cout << "Error cannot open outfile" << endl;
		  exit(0);
		}
	}

}
