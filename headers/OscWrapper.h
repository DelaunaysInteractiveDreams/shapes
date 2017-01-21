#ifndef OSCWRAPPER_H
#define OSCWRAPPER_H


#include "FileManager.h"
#include "ofxAbletonLive.h"

namespace idl {

class OscWrapper
{
private:
	ofxAbletonLive *oscInterface;
	json soundParameterList;
	OscWrapper();
	~OscWrapper();
	std::map<string, float> originalValues;

public:
	static OscWrapper& getInstance();
	float getOriginValue(string p);
	void sendValue(string parameter, float value);

	void setOSCInterface(ofxAbletonLive * live);
};
}

#endif