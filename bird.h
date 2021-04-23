#ifndef ANIMAL_H
#define ANIMAL_H

#include <vector>
#include <memory>
#include "ppmR.h"
#include "color.h"
#include "rect.h"
#include "ellipse.h"
#include "polygon.h"
#include "vec2.h"
#include <map>

class Animal {
    public:
    Animal(ellipse& body, std::vector<ellipse>& e, std::vector<Polygon>& b, std::vector<Polygon>& t, std::vector<Polygon>& eb, ellipse& bell) {
        bodyRound(body);
        eyes(e);
        beak(b);
        tail(t);
        eyebrows(eb);
        belly(bell);
        isRound = true;
    }

    Animal(Polygon& body, std::vector<ellipse>& e, std::vector<Polygon>& b, std::vector<Polygon>& t, std::vector<Polygon>& eb, ellipse& bell) {
        bodyTriangle(body);
        eyes(e);
        beak(b);
        tail(t);
        eyebrows(eb);
        belly(bell);
        isRound = false;
    }
	
    unordered_map<string, color> mainColors;
    mainColors["black"] = color(0, 0, 0);
    mainColors["white"] = color(255, 255, 255);
    mainColors["beakColor"] = color(255, 175, 0);

    ellipse& getBodyE() { return bodyRound; }
    Polygon& getBodyP() { return bodyTriangle; }
    std::vector<ellipse>& getEyes() { return eyes; }
    std::vector<Polygon>& getBeak() { return beak; }
    std::vector<Polgon>& getTail() { return tail; }
    std::vector<Polgon>& getEyebrows() { return eyebrows; }
    ellipse& getBelly() { return belly; }

    bool eval(double x, double y) {
        if (isRound) {
            if (bodyRound.eval(x,y) < 1) {
                return true;
            }
        } else {
            if (bodyTriangle.eval(x,y)) {
                return true;
            }
        }
        for (int i = 0; i < 100; i++) {
            if (eyes.at(i).eval(x,y) < 1 || belly.eval(x,y) < 1 || beak.at(i).eval(x,y) || tail.at(i).eval(x,y) || eyebrows.at(i).eval(x,y)) {
                return true;
            }
        }
		return false;
	}


    private:
        bool isRound;
        ellipse& bodyRound;
        Polygon& bodyTriangle;
        std::vector<ellipse>& eyes;
        std::vector<Polygon>& beak;
        std::vector<Polygon>& tail;
        std::vector<Polygon>& eyebrows;
        ellipse& belly;
    


};




#endif
