#ifndef BIRD_H
#define BIRD_H

#include <vector>
#include <memory>
#include <unordered_map>
#include "ppmR.h"
#include "color.h"
#include "rect.h"
#include "ellipse.h"
#include "polygon.h"
#include "vec2.h"

class Bird {
    public:
    Bird(ellipse& body, std::vector<ellipse>& e, std::vector<Polygon>& b,
      std::vector<Polygon>& t, std::vector<Polygon>& eb, ellipse& bell):
      bodyRound(body), eyes(e), beak(b), tail(t), eyebrows(eb), belly(bell) {}

    ellipse& getBodyE() { return bodyRound; }
    std::vector<ellipse>& getEyes() { return eyes; }
    std::vector<Polygon>& getBeak() { return beak; }
    std::vector<Polygon>& getTail() { return tail; }
    std::vector<Polygon>& getEyebrows() { return eyebrows; }
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
  		  if (res && obj.getDepth() > curDepth) {
  			inC = obj.getInC();
  			inTrue = true;
  			curDepth = obj.getDepth();
  		  }
  		}


      if (bodyRound.eval(x,y) < 0) {
              inC = bodyRound.getInC();
              if (belly.eval(x,y) < 0) {
                inC = belly.getInC();
              }
              inTrue = true;
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
   		  if (res && obj.getDepth() > curDepth) {
   			inC = obj.getInC();
   			inTrue = true;
   			curDepth = obj.getDepth();
   		  }
   		 }

      curDepth = -1.0;
   		for (auto obj : beak) {
   		  res = obj.eval(x, y);
   		  if (res && obj.getDepth() > curDepth) {
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


          bodyRound.translate(offset); // does this need & ?

      for (ellipse & e : eyes) {
        e.translate(offset);
      }
      for (Polygon & b : beak) {
        b.translate(offset);
      }
      for (Polygon & t : tail) {
        t.translate(offset);
      }
      for (Polygon & e : eyebrows) {
        e.translate(offset);
      }
      belly.translate(offset); // does this need & ?

      return;
    }



    private:
        ellipse& bodyRound;
        std::vector<ellipse>& eyes;
        std::vector<Polygon>& beak;
        std::vector<Polygon>& tail;
        std::vector<Polygon>& eyebrows;
        ellipse& belly;

};




#endif
