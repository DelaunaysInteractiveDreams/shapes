#ifndef WORLD_H
#define WORLD_H

#include <list>

#include "ofMain.h"
#include "shape.h"


namespace idl {

class World {
	std::list<Shape> shapes;
	std::list<Shape>::iterator selector;
	
public:
	World();
        
        void setup();
        
	/* Returns a reference to the current shape. */
	Shape & currentShape();
	/* Returns true if selector is at the end. */
	bool endShape();
	/* Select the first shape. Returns false if there isn't one. */
	bool firstShape();
	/* Select next shape. Returns false of end is reached. */
	bool nextShape();
};

}

#endif