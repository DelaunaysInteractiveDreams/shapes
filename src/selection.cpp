#include "selection.h"
#include "Utility.h"

using namespace idl;
using namespace std;

Selection::Selection(): world(World::getInstance()) {

}

void Selection::uniform(float weight){
	for(world.firstShape(); !world.endShape(); world.nextShape()) {
		shapes.push_back(ShapeSelected(&world.currentShape(), weight));
	}
}

void Selection::radial(float weight, ofPoint point, float radius){
	for(world.firstShape(); !world.endShape(); world.nextShape()) {
		float dist = (point - world.currentShape().getPosition()).length();
		float w;
		if(dist > radius) {
			w = 0;
		} else {
			w = (1 - dist / radius) * weight;
		}
		shapes.push_back(ShapeSelected(&world.currentShape(), w));
	}
}

void Selection::byId(string id){
	for(world.firstShape(); !world.endShape(); world.nextShape()) {

		//TODO better
		vector<string> ids = parseIds(world.currentShape().getId());
		for (std::vector<string>::iterator it = ids.begin() ; it != ids.end(); ++it){
			if (id == (*it))
				shapes.push_back(ShapeSelected(&world.currentShape(), 1));
		}

	}
}

void Selection::byColor(string _color){
	ofColor color = parseColor(_color);
	for(world.firstShape(); !world.endShape(); world.nextShape()) {
			if (color == world.currentShape().getColor())
				shapes.push_back(ShapeSelected(&world.currentShape(), 1));
	}
}

void Selection::random(float threshold){
	srand(time(NULL));
	for(world.firstShape(); !world.endShape(); world.nextShape()) {
		float weight = ofRandom(0, 1);
		if (weight >threshold)
				shapes.push_back(ShapeSelected(&world.currentShape(), weight));
	}
}

void Selection::intersection(vector<shared_ptr<Selection>> s){
	if (s.empty()) return;
	shared_ptr<Selection> s1 = *(s.begin());
	for(auto it = s.begin()+1; it != s.end(); ++it) {
		if (!(*it)) continue;
		vector<ShapeSelected> intersection = intersectionTwo(*s1, *(*it));
		s1->shapes = intersection;
	}
	shapes = s1->shapes;
}

vector<ShapeSelected> Selection::intersectionTwo(Selection& s1, Selection& s2){
	vector<ShapeSelected> intersection;
	for(auto it1 = s1.shapes.begin(); it1 != s1.shapes.end(); ++it1){
		for(auto it2 = s2.shapes.begin(); it2 != s2.shapes.end(); ++it2){
				if (*it1 == *it2 ){
					ShapeSelected shape = *it1;
					intersection.push_back(shape);
				}
			}
	}
	return intersection;
}
