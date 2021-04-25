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
#include "pig.h"

using namespace std;

/*write out PPM data, using the defined implicit equation
  interior points write a different color then exterior points */

void writeOut(ostream& out, ppmR& theWriter, Bird blackBird, Pig piggy) {

	float res;
	color inC;
	color drawC;
	color background(12, 34, 56);
	bool inTrue = false;
	double curDepth = -1.0;

	//for every point in the 2D space
	for (int y=0; y < theWriter.height; y++) {
		for (int x =0; x < theWriter.width; x++) {
			drawC = blackBird.eval(x, y, background);
			theWriter.writePixel(out, x, y, drawC);
			drawC = piggy.eval(x, y, background);
			theWriter.writePixel(out, x, y, drawC);
		}
			/*
			if (drawC == background) {
				//do nothing
			} else {
				inTrue = true;
				inC = drawC;
			}
			*/

			/*
			inTrue = false;
			curDepth = -1;
			*/
			//iterate through all possible equations (note 'front' determined by order in vector)

			/*
			if (inTrue) {
				theWriter.writePixel(out, x, y, inC);
			}
			else
				theWriter.writePixel(out, x, y, background);
		}
		*/
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

	unordered_map<string, color> pigColors;
	pigColors["green"] = color(13, 186, 22);
	pigColors["outlined green"] = color(5, 132, 12);
	pigColors["dark green"] = color(38, 115, 42);

	ofstream outFile;
	int sizeX, sizeY;



	vector<color> niceC;
	niceC.push_back(color(117, 119, 186));
	niceC.push_back(color(45, 47, 135));
	niceC.push_back(color(174, 209, 238));
	niceC.push_back(color(239, 174, 115));
	niceC.push_back(color(186, 140, 117));

	ellipse blackBirdBody(vec2(30,30), vec2(20,20), 1.0, mainColors["black"]);
	vector<ellipse> blackBirdEyes;
	blackBirdEyes.push_back(ellipse(vec2(20,20), vec2(5,6), 2.0, blackBirdColors["tinted black"]));
	blackBirdEyes.push_back(ellipse(vec2(40,20), vec2(5,6), 2.0, blackBirdColors["tinted black"]));
	blackBirdEyes.push_back(ellipse(vec2(20,20), vec2(4,4), 3.0, mainColors["white"]));
	blackBirdEyes.push_back(ellipse(vec2(40,20), vec2(4,4), 3.0, mainColors["white"]));
	blackBirdEyes.push_back(ellipse(vec2(20,20), vec2(2,2), 4.0, mainColors["black"]));
	blackBirdEyes.push_back(ellipse(vec2(40,20), vec2(2,2), 4.0, mainColors["black"]));

	vector<Polygon> blackBirdBeak;
	vector<Polygon> blackBirdTail;
	vector<Polygon> blackBirdEyebrows;
	vector<vec2> blackBirdUpperBeak;
	blackBirdUpperBeak.push_back(vec2(30, 25));
	blackBirdUpperBeak.push_back(vec2(40, 27));
	blackBirdUpperBeak.push_back(vec2(30, 30));

	vector<vec2> blackBirdLowerBeak;
	blackBirdLowerBeak.push_back(vec2(30, 32));
	blackBirdLowerBeak.push_back(vec2(40, 34));
	blackBirdLowerBeak.push_back(vec2(30, 37));
	blackBirdBeak.push_back(Polygon(blackBirdUpperBeak, 2.0, mainColors["beakColor"]));
	blackBirdBeak.push_back(Polygon(blackBirdLowerBeak, 2.0, mainColors["beakColor"]));

	vector<vec2> blackBirdHair;
	blackBirdHair.push_back(vec2(28,11));
	blackBirdHair.push_back(vec2(27,5));
	blackBirdHair.push_back(vec2(33,5));
	blackBirdHair.push_back(vec2(32,11));

	vector<vec2> blackBirdHairOrange;
	blackBirdHair.push_back(vec2(27,5));
	blackBirdHair.push_back(vec2(27,2));
	blackBirdHair.push_back(vec2(33,2));
	blackBirdHair.push_back(vec2(33,5));
	blackBirdTail.push_back(Polygon(blackBirdHair, 2.0, mainColors["black"]));
	blackBirdTail.push_back(Polygon(blackBirdHair, 3.0, blackBirdColors["red"]));

	vector<vec2> blackBirdLEyebrow;
	blackBirdHair.push_back(vec2(10,15));
	blackBirdHair.push_back(vec2(12,11));
	blackBirdHair.push_back(vec2(24,11));
	blackBirdHair.push_back(vec2(22,15));

	vector<vec2> blackBirdREyebrow;
	blackBirdHair.push_back(vec2(38,15));
	blackBirdHair.push_back(vec2(36,11));
	blackBirdHair.push_back(vec2(48,11));
	blackBirdHair.push_back(vec2(50,15));
	blackBirdTail.push_back(Polygon(blackBirdHair, 4.0, blackBirdColors["red"]));
	blackBirdTail.push_back(Polygon(blackBirdHair, 4.0, blackBirdColors["red"]));

	ellipse blackBirdBelly(vec2(30, 40), vec2(8,8), 2.0, blackBirdColors["tinted black"]);
	Bird blackBird(blackBirdBody, blackBirdEyes, blackBirdBeak, blackBirdTail, blackBirdEyebrows, blackBirdBelly);

	// CREATING PIG
	ellipse pigBody(vec2(150,150), vec2(120,80), 1, pigColors["green"]);
	vector<ellipse> pigEyes;
	pigEyes.push_back(ellipse(vec2(210,140), vec2(20,20), 2, mainColors["white"]));
	pigEyes.push_back(ellipse(vec2(90,140), vec2(20,20), 2, mainColors["white"]));
	pigEyes.push_back(ellipse(vec2(220,140), vec2(8,8), 3, mainColors["black"]));
	pigEyes.push_back(ellipse(vec2(80,140), vec2(8,8), 3, mainColors["black"]));

	vector<ellipse> pigSnout;
	pigSnout.push_back(ellipse(vec2(150,160), vec2(38,28), 2, pigColors["outlined green"]));
	pigSnout.push_back(ellipse(vec2(150,160), vec2(35,25), 3, pigColors["green"]));
	pigSnout.push_back(ellipse(vec2(130,160), vec2(8,12), 4, mainColors["black"]));
	pigSnout.push_back(ellipse(vec2(170,160), vec2(8,8), 4, mainColors["black"]));

	vector<ellipse> pigEars;
	pigEars.push_back(ellipse(vec2(100,75), vec2(20,20), 2, pigColors["green"]));
	pigEars.push_back(ellipse(vec2(200,75), vec2(20,20), 2, pigColors["green"]));
	pigEars.push_back(ellipse(vec2(100,75), vec2(12,12), 3, pigColors["outlined green"]));
	pigEars.push_back(ellipse(vec2(200,75), vec2(12,12), 3, pigColors["outlined green"]));

	Pig piggy(pigBody, pigEyes, pigSnout, pigEars);



	if (argc < 4) {
		cerr << "Error format: a.out sizeX sizeY outfileName" << endl;
		exit(0);
	}

	string outFilename;
	sizeX = stoi(argv[1]);
	sizeY = stoi(argv[2]);
	ppmR theWriter(sizeX, sizeY);

	cout << "sizeX: " << sizeX << " sizeY: " << sizeY << endl;


	//create a vector of vertices for the triangle
	//vertices specified counter clockwise!


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
		  /*for (auto s : theEllipses) {
		  	s->translate(trans1);
		  }
		  for (auto p : thePolys) {
		  	p->translate(trans3);
		  }
		  for (auto r : theRects) {
		  	r->translate(trans2);
		  }
		  */

		  writeOut(outFile, theWriter, blackBird, piggy);
		  outFile.close();
		  outFilename.erase();
		} else {
		  cout << "Error cannot open outfile" << endl;
		  exit(0);
		}
	}

}
