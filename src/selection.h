#ifndef SELECTION_H
#define SELECTION_H

#include <vector>
#include <memory>

#include "ofMain.h"
#include "shape.h"
#include "world.h"

namespace idl {
	
typedef std::pair<Shape*, float> ShapeSelected;

struct Selection {
	std::vector< ShapeSelected > weights;
	
	Selection();
	
	void uniform(World & world, float weight);
	void distance(World & world, float weight, ofPoint point, float radius);
};

}

#endif