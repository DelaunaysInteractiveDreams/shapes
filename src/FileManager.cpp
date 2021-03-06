#include "FileManager.h"
#include "Utility.h"
#include "OscWrapper.h"

#include <fstream>
#include <iostream>
#include <world.h>

using namespace idl;
using namespace std;

FileManager::FileManager(string path)
	: sessionDirectory(path) {
	if(!sessionDirectory.exists()) {
		cerr << "Error this directory doesn't exist : " << sessionDirectory.getAbsolutePath() << endl;
	}
	/* Load dreams list */
	json d = loadJSONFile("Dreams", false);
	dreams = d.get<vector<string> >();
	
	dream_index = 0;
	currentDream = dreams[dream_index];
}


FileManager & FileManager::getInstance(string path) {
	static FileManager instance(path);
	return instance;
}

void FileManager::init(string path) {
	getInstance(path);
}

json FileManager::loadJSONFile(string file, bool dreamDir) {
	string path = sessionDirectory.getAbsolutePath();
	if (dreamDir)
		path += "/" + currentDream;
	path += "/" + file + ".json";
	cout << "Loading file : " << path << endl;
	ifstream fileStream(path);
	json j;
	if(!fileStream) {
		cerr << "Cannot open file : " << path << endl;
		return j;
	}
	j << fileStream;
	return j;
}

ofxSVG FileManager::loadSVGFile(string path) {
	ofxSVG svg;
	path =  sessionDirectory.getAbsolutePath() + "/" + path + ".svg";
	cout << "Loading file : " << path << endl;
	svg.load(path);
	return svg;
}

ofVideoPlayer FileManager::loadMovBackground(string path){
	ofVideoPlayer background;
	// path =  sessionDirectory.getAbsolutePath() + "/background/" + path + ".mov";
	// cout << "Loading file : " << path << endl;
	// background.load(path);
	return background;
}

void FileManager::initActions(std::map<std::string, json>& actions){
	ofDirectory dir(sessionDirectory.getAbsolutePath() + "/actions");
	auto files = dir.getFiles();
	for (auto& f : files) {
		auto fileName = split(f.getFileName(), '.')[0];
		actions[fileName] = loadJSONFile("actions/" + fileName);
	}
}

void FileManager::setCurrentDream(string _currentDream) {
	currentDream = _currentDream;
}

bool FileManager::nextDream_building() {
	bool end = (dream_index == dreams.size() - 1);
	dream_index = (dream_index + 1) % dreams.size();
	currentDream = dreams[dream_index];
	return !end;
}

void FileManager::nextDream_UpdateWorld() {
	nextDream_building();
	World::getInstance().setCurrentDream(dream_index);
	OscWrapper::getInstance().changeScene(currentDream);
}



