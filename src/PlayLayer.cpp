#include <Geode/modify/PlayLayer.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

/*
	original code from GDMO written by Maxnu and SpaghettDev, which is published
	under the GPLv3 license. code re-use + adaptation compatible with LGPLv2
	per the GNU license compatibility matrix seen here:
	
	https://www.gnu.org/licenses/gpl-faq.en.html#AllCompatibility
	
	and here:
	
	https://www.gnu.org/licenses/gpl-faq.en.html#compat-matrix-footnote-7
*/

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
	void onExit() {
		Manager::getSharedInstance()->isPracticeMode = this->m_isPracticeMode;
		Utils::checkForCompactEndscreen();
		PlayLayer::onExit();
	}
};