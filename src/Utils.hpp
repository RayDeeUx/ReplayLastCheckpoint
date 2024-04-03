#pragma once

#include "Manager.hpp"

using namespace geode::prelude;

namespace Utils {
	bool isLevelComplete();
	bool get(std::string settingName);
	bool getModSavedSetting(std::string modID, std::string theirSetting);
	bool notQualified(EndLevelLayer* ell);
	
	void checkForCompactEndscreen();
}