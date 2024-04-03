#include <Geode/modify/PlayLayer.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyPlayLayer, PlayLayer) {
	void levelComplete() {
		auto manager = Manager::getSharedInstance();
		manager->isLevelComplete = true;
		manager->isPracticeMode = this->m_isPracticeMode;
		Utils::checkForCompactEndscreen();
		PlayLayer::levelComplete();
	}
	void resetLevel() {
		auto manager = Manager::getSharedInstance();
		manager->isLevelComplete = false;
		manager->isPracticeMode = this->m_isPracticeMode;
		Utils::checkForCompactEndscreen();
		PlayLayer::resetLevel();
	}
	void onQuit() {
		auto manager = Manager::getSharedInstance();
		manager->isLevelComplete = false;
		manager->isPracticeMode = false;
		Utils::checkForCompactEndscreen();
		PlayLayer::onQuit();
	}
	#ifndef GEODE_IS_MACOS
	void onExit() {
		Manager::getSharedInstance()->isPracticeMode = this->m_isPracticeMode;
		Utils::checkForCompactEndscreen();
		PlayLayer::onExit();
	}
	#endif
};