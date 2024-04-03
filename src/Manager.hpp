#pragma once

using namespace geode::prelude;

class Manager {

protected:
	static Manager* instance;
public:

	bool isLevelComplete = false;
	bool isPracticeMode = false;
	bool isCompactEndscreen = false;
	
	float yPositionOneFourths = -125.f;
	float yPositionThreeFourths = -125.f;
	float xPositionOneFourths = 145.f;
	float xPositionThreeFourths = 55.f;

	static Manager* getSharedInstance() {

		if (!instance) {
			instance = new Manager();
		};
		return instance;
	}

};