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
			
			inTrue = false;
			drawC = blackBird.eval(x, y, background);
			// theWriter.writePixel(out, x, y, drawC);
			if (drawC == background) {
				//do nothing
			} else {
				inTrue = true;
				inC = drawC;
			}
			drawC = piggy.eval(x, y, background);
			if (drawC == background) {
				//do nothing
			} else {
				inTrue = true;
				inC = drawC;
			}

			if (inTrue) {			
				theWriter.writePixel(out, x, y, inC);
			}
			else
				theWriter.writePixel(out, x, y, background);
			//theWriter.writePixel(out, x, y, inC);
		}
			
		theWriter.writeNewLine(out);
	}
}


/*read command line arguments and write out new ascii file of given size */
int main(int argc, char *argv[]) {

	// Colors

	unordered_map<string, color> mainColors;
	mainColors["black"] = color(0, 0, 0);
	mainColors["white"] = color(255, 255, 255);
	mainColors["beakColor"] = color(255, 175, 0);

	unordered_map<string, color> blackBirdColors;
	blackBirdColors["tinted black"] = color(68, 68, 68);
	blackBirdColors["red"] = color(198, 68, 0);

	unordered_map<string, color> pigColors;
	pigColors["green"] = color(13, 186, 22);
	pigColors["outlined green"] = color(5, 132, 12);
	pigColors["dark green"] = color(38, 115, 42);

	vector<color> niceC;
	niceC.push_back(color(117, 119, 186));
	niceC.push_back(color(45, 47, 135));
	niceC.push_back(color(174, 209, 238));
	niceC.push_back(color(239, 174, 115));
	niceC.push_back(color(186, 140, 117));

	// Creating BlackBird

	ellipse blackBirdBody(vec2(640,340), vec2(100,100), 1.0, mainColors["black"]);
	vector<ellipse> blackBirdEyes;
	blackBirdEyes.push_back(ellipse(vec2(590,290), vec2(20,20), 2.0, blackBirdColors["tinted black"])); //change this color
	blackBirdEyes.push_back(ellipse(vec2(690,290), vec2(20,20), 2.0, blackBirdColors["tinted black"])); //change this color
	blackBirdEyes.push_back(ellipse(vec2(590,290), vec2(15,15), 3.0, mainColors["white"])); 
	blackBirdEyes.push_back(ellipse(vec2(690,290), vec2(15,15), 3.0, mainColors["white"]));
	blackBirdEyes.push_back(ellipse(vec2(590,290), vec2(8,8), 4.0, mainColors["black"]));
	blackBirdEyes.push_back(ellipse(vec2(690,290), vec2(8,8), 4.0, mainColors["black"]));


	vector<Polygon> blackBirdBeak;
	vector<Polygon> blackBirdTail;
	vector<Polygon> blackBirdEyebrows;
	vector<vec2> blackBirdUpperBeak;
	blackBirdUpperBeak.push_back(vec2(640, 320));
	blackBirdUpperBeak.push_back(vec2(690, 330));
	blackBirdUpperBeak.push_back(vec2(640, 340));

	vector<vec2> blackBirdLowerBeak;
	blackBirdLowerBeak.push_back(vec2(640, 350));
	blackBirdLowerBeak.push_back(vec2(690, 360));
	blackBirdLowerBeak.push_back(vec2(640, 370));
	blackBirdBeak.push_back(Polygon(blackBirdUpperBeak, 2.0, mainColors["beakColor"]));
	blackBirdBeak.push_back(Polygon(blackBirdLowerBeak, 2.0, mainColors["beakColor"]));

	vector<vec2> blackBirdHair;
	blackBirdHair.push_back(vec2(630,200));
	blackBirdHair.push_back(vec2(650,200));
	blackBirdHair.push_back(vec2(650,240));
	blackBirdHair.push_back(vec2(630,240));

	vector<vec2> blackBirdHairOrange;
	blackBirdHairOrange.push_back(vec2(630,179));
	blackBirdHairOrange.push_back(vec2(650,179));
	blackBirdHairOrange.push_back(vec2(650,199));
	blackBirdHairOrange.push_back(vec2(630,199));

	blackBirdTail.push_back(Polygon(blackBirdHair, 2.0, mainColors["black"]));
	blackBirdTail.push_back(Polygon(blackBirdHairOrange, 3.0, blackBirdColors["red"]));

	vector<vec2> blackBirdLEyebrow;
	blackBirdLEyebrow.push_back(vec2(570,260));
	blackBirdLEyebrow.push_back(vec2(610,260));
	blackBirdLEyebrow.push_back(vec2(610,280));
	blackBirdLEyebrow.push_back(vec2(570,280));

	vector<vec2> blackBirdREyebrow;
	blackBirdREyebrow.push_back(vec2(670,260));
	blackBirdREyebrow.push_back(vec2(710,260));
	blackBirdREyebrow.push_back(vec2(710,280));
	blackBirdREyebrow.push_back(vec2(670,280));

	blackBirdEyebrows.push_back(Polygon(blackBirdREyebrow, 4.0, blackBirdColors["red"]));
	blackBirdEyebrows.push_back(Polygon(blackBirdLEyebrow, 4.0, blackBirdColors["red"]));

	ellipse blackBirdBelly(vec2(640, 420), vec2(50,30), 2.0, blackBirdColors["tinted black"]);
	Bird blackBird(blackBirdBody, blackBirdEyes, blackBirdBeak, blackBirdTail, blackBirdEyebrows, blackBirdBelly);

	// CREATING PIG
	ellipse pigBody(vec2(450,150), vec2(120,80), 1, pigColors["green"]);
	vector<ellipse> pigEyes;
	pigEyes.push_back(ellipse(vec2(510,140), vec2(23,23), 1, pigColors["outlined green"]));
	pigEyes.push_back(ellipse(vec2(510,140), vec2(20,20), 2, mainColors["white"]));
	pigEyes.push_back(ellipse(vec2(390,140), vec2(23,23), 1, pigColors["outlined green"]));
	pigEyes.push_back(ellipse(vec2(390,140), vec2(20,20), 2, mainColors["white"]));
	pigEyes.push_back(ellipse(vec2(520,140), vec2(8,8), 3, mainColors["black"]));
	pigEyes.push_back(ellipse(vec2(380,140), vec2(8,8), 3, mainColors["black"]));

	vector<ellipse> pigSnout;
	pigSnout.push_back(ellipse(vec2(450,160), vec2(38,33), 2, pigColors["outlined green"]));
	pigSnout.push_back(ellipse(vec2(450,160), vec2(35,30), 3, pigColors["green"]));
	pigSnout.push_back(ellipse(vec2(435,160), vec2(8,11), 4, mainColors["black"]));
	pigSnout.push_back(ellipse(vec2(465,160), vec2(8,8), 4, mainColors["black"]));

	vector<ellipse> pigEars;
	pigEars.push_back(ellipse(vec2(400,75), vec2(20,20), 2, pigColors["green"]));
	pigEars.push_back(ellipse(vec2(500,75), vec2(20,20), 2, pigColors["green"]));
	pigEars.push_back(ellipse(vec2(400,75), vec2(12,12), 3, pigColors["outlined green"]));
	pigEars.push_back(ellipse(vec2(500,75), vec2(12,12), 3, pigColors["outlined green"]));

	vector<Polygon> pigEyebrows;
	vector<vec2> pigLEyebrow;
	pigLEyebrow.push_back(vec2(420,100));
	pigLEyebrow.push_back(vec2(420,110));
	pigLEyebrow.push_back(vec2(370,115));
	pigLEyebrow.push_back(vec2(370,110));

	vector<vec2> pigREyebrow;
	pigREyebrow.push_back(vec2(490,100));
	pigREyebrow.push_back(vec2(540,110));
	pigREyebrow.push_back(vec2(540,115));
	pigREyebrow.push_back(vec2(490,110));

	pigEyebrows.push_back(Polygon(pigLEyebrow, 3, pigColors["dark green"]));
	pigEyebrows.push_back(Polygon(pigREyebrow, 3, pigColors["dark green"]));

	Pig piggy(pigBody, pigEyes, pigSnout, pigEars, pigEyebrows);


	ofstream outFile;
	int sizeX, sizeY;

	if (argc < 4) {
		cerr << "Error format: a.out sizeX sizeY outfileName" << endl;
		exit(0);
	}

	string outFilename;
	sizeX = stoi(argv[1]);
	sizeY = stoi(argv[2]);
	ppmR theWriter(sizeX, sizeY);

	cout << "sizeX: " << sizeX << " sizeY: " << sizeY << endl;

	//you will use these
	vec2 trans1(-1, 1);
	vec2 trans2(1, 1);
	// vec2 trans3(-1, -1); // not in use
	vec2 accel(0, 1);

	//loop through and produce more than on image - change to 30
	for (int i=0; i < 3; i++) {

	  //set up unique filename that conforms to processing movie maker
	  outFilename.append(argv[3]);
	  if (i < 10)
		outFilename.append(to_string(0));
		outFilename.append(to_string(i));
		outFilename.append(".ppm");

	  trans1 = trans1 + accel;
	  trans2 = trans2 + accel;
	  //trans3 = trans3 + accel;

		//open new file
		outFile.open(outFilename);
		if (outFile) {
		  cout << "writing an image of size: " << sizeX << " " << sizeY << " to: " << argv[3] << endl;
		  theWriter.writeHeader(outFile);

			blackBird.translate(trans1);
			piggy.translate(trans2);

		  writeOut(outFile, theWriter, blackBird, piggy);
		  outFile.close();
		  outFilename.erase();
		} else {
		  cout << "Error cannot open outfile" << endl;
		  exit(0);
		}
	}

}
