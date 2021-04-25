#ifndef PIG_H
#define PIG_H

#include <vector>
#include <memory>
#include <unordered_map>
#include "ppmR.h"
#include "color.h"
#include "rect.h"
#include "ellipse.h"
#include "polygon.h"
#include "vec2.h"

class Pig {
    public:
    Pig(ellipse& body, std::vector<ellipse>& ey, std::vector<ellipse>& b,
      std::vector<ellipse>& ear, std::vector<Polygon>& eb):
      bodyRound(body), eyes(ey), snout(b), ears(ear), eyebrows(eb) {}

    ellipse& getBodyE() { return bodyRound; }
    std::vector<ellipse>& getEyes() { return eyes; }
    std::vector<ellipse>& getSnout() { return snout; }
    std::vector<ellipse>& getEars() { return ears; }
    std::vector<Polygon>& getEyebrows() { return eyebrows; }

    color eval(int x, int y, color background) {

      float res;
      color inC;
      bool inTrue = false;
      double curDepth = -1.0;


      if (bodyRound.eval(x,y) < 0) {
              inC = bodyRound.getInC();
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
      for (auto obj : snout) {
        res = obj.eval(x, y);
        if (res < 0 && obj.getDepth() > curDepth) {
        inC = obj.getInC();
        inTrue = true;
        curDepth = obj.getDepth();
        }
       }

      curDepth = -1.0;
      for (auto obj : ears) {
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
      for (ellipse & s : snout) {
        s.translate(offset);
      }
      for (ellipse & t : ears) {
        t.translate(offset);
      }
      for (Polygon & e : eyebrows) {
        e.translate(offset);
      }

      return;
    }



    private:
        ellipse& bodyRound;
        std::vector<ellipse>& eyes;
        std::vector<ellipse>& snout;
        std::vector<ellipse>& ears;
        std::vector<Polygon>& eyebrows;
};




#endif
