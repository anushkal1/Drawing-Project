#ifndef ANIMAL_H
#define ANIMAL_H

#include <vector>
#include <memory>
#include <unordered_map>
#include "ppmR.h"
#include "color.h"
#include "rect.h"
#include "ellipse.h"
#include "polygon.h"
#include "vec2.h"

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

    color eval(int x, int y, color background) {

      // this looks really inefficient and redundant and it is
      // but afaik can't really do anything about it bc of the type differences

      float res;
  		color inC;
  		bool inTrue = false;
  		double curDepth = -1.0;

      for (auto obj : tail) {
  		  res = obj.eval(x, y);
  		  if (res < 0 && obj.getDepth() > curDepth) {
  			inC = obj.getInC();
  			inTrue = true;
  			curDepth = obj.getDepth();
  		  }
  		}

      if (isRound) {
          if (bodyRound.eval(x,y) < 1) {
              inC = bodyRound.getInC();
              if (belly.eval(x,y)) {
                inC = belly.getInC();
              }
              inTrue = true;
          }
      } else {
          if (bodyTriangle.eval(x,y)) {
              inC = bodyTriangle.getInC();
              if (belly.eval(x,y)) {
                inC = belly.getInC();
              }
              inTrue = true;
          }
      }

      curDepth = -1.0;
  		for (auto obj : eyes) {
  		  res = obj.eval(x, y);
  		  if (res < 0 && obj.getDepth() > curDepth) {
  			inC = obj.getInC();
  			inTrue = true;
  			curDepth = obj.getDepth();
  		  }
  		 }

      curDepth = -1.0;
   		for (auto obj : eyebrows) {
   		  res = obj.eval(x, y);
   		  if (res < 0 && obj.getDepth() > curDepth) {
   			inC = obj.getInC();
   			inTrue = true;
   			curDepth = obj.getDepth();
   		  }
   		 }

      curDepth = -1.0;
   		for (auto obj : beak) {
   		  res = obj.eval(x, y);
   		  if (res < 0 && obj.getDepth() > curDepth) {
   			inC = obj.getInC();
   			inTrue = true;
   			curDepth = obj.getDepth();
   		  }
   		 }

  		if (inTrue) {
  			return inC;
  		}
  		else
  			return background;

    }

    void translate(vec2 offset) {

      if (isRound) {
          bodyRound.translate(offset); // does this need & ?
      } else {
          bodyTriangle.translate(offset); // does this need & ?
      }
      for (ellipse & e : eyes) {
        poly.translate(offset);
      }
      for (Polygon & p : beak) {
        p.translate(offset);
      }
      for (Polygon & p : tail) {
        p.translate(offset);
      }
      for (Polygon & p : eyebrows) {
        p.translate(offset);
      }
      belly.translate(offset); // does this need & ?

      return;
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
