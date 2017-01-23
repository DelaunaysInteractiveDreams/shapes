#include "ModifierFactory.h"
#include "SeedFactory.h"
#include "SeedConstant.h"
#include "SelectionFactory.h"
#include "Utility.h"
#include "ModifierScale.h"
#include "ModifierRotation.h"
#include "ModifierSoundSetter.h"
#include "OscWrapper.h"
#include "ModifierColor.h"
#include <string>

using namespace std;
using namespace idl;

ModifierFactory::ModifierFactory() {

}

ModifierFactory & idl::ModifierFactory::getInstance(){
	static ModifierFactory instance;
	return instance;
}

shared_ptr<Seed> getSeed(json& jModifier) {
	if (jModifier.find("seed") != jModifier.end()) {
		return SeedFactory::getInstance().
			createSeed(jModifier["seed"].get<string>());
	}
	return shared_ptr<Seed>(new SeedConstant());
}


shared_ptr<Modifier> ModifierFactory::create(json& jModifier) {
	try {
		string type = jModifier["type"];
		auto args = split(type, ' ');
		if (args[0] == "selection") {
			shared_ptr<Selection> selection = SelectionFactory::getInstance().create(jModifier["selection"]);
			if (args[1] == "dependante") {
				/*Seed Recupération*/
				shared_ptr<Seed> seed = getSeed(jModifier);
				/*Rotation*/
				if (args[2] == "rotation") {
					cout << "Angle :" << jModifier["angle"] << endl;
					float angle = jModifier["angle"].get<float>();
					bool indiv = jModifier["individual_origin"].get<bool>();
					ofPoint pivot(0, 0);
					if (jModifier.find("pivot") != jModifier.end()) {
						pivot = parsePoint(jModifier["pivot"].get<string>());
					}
					return shared_ptr<Modifier>(new Rotator(selection, angle, indiv, pivot, seed));
				}
				/*Scale*/
				if (args[2] == "scale") {
					ofVec2f scale = parseVec2(jModifier["scale"]);
					bool indiv = jModifier["individual_origin"].get<bool>();
					ofPoint pivot(0, 0);
					if (jModifier.find("pivot") != jModifier.end()) {
						pivot = parsePoint(jModifier["pivot"].get<string>());
					}
					return shared_ptr<Modifier>(new Scalator(selection, scale, indiv, pivot, seed));
				}
				/*Color*/
				if (args[2] == "color") {
					ofColor color = parseColor(jModifier["color"]);
					return shared_ptr<Modifier>(new Colorizer(selection, color, seed));
				}
			}
		}
		if (args[0] == "dependante") {
			shared_ptr<Seed> seed = getSeed(jModifier);
			if (args[1] == "sound") {
				float value = jModifier["value"].get<float>();
				string param = jModifier["controller"].get<string>();
				return shared_ptr<Modifier>(new ModifierSoundSetter(seed, value, param));
			}
		}
	}catch (exception& e) {
		cerr << e.what() << endl;
		return nullptr;
	}
}

ModifierFactory::~ModifierFactory(){

}