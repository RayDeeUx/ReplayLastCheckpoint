#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::cocos;

namespace Utils {
	bool isLevelComplete() {
		return Manager::getSharedInstance()->isLevelComplete;
	}
	bool get(std::string settingName) {
		return Mod::get()->getSettingValue<bool>(settingName);
	}
	bool getModSavedSetting(std::string modID, std::string theirSetting) {
		return (
			Loader::get()->isModLoaded(modID) &&
			Loader::get()->getLoadedMod(modID)->getSavedValue<bool>(theirSetting)
		);
	}
	bool notQualified(EndLevelLayer* ell) {
		return (!Utils::get("enabled") || Utils::getModSavedSetting("maxnu.gd_mega_overlay", "level/replay_checkpoint") || ell->getChildByIDRecursive("absolllute.megahack/practice-replay-button") != nullptr || !Manager::getSharedInstance()->isPracticeMode);
	}
	void checkForCompactEndscreen() {
		auto manager = Manager::getSharedInstance();
		manager->isCompactEndscreen = Loader::get()->isModLoaded("suntle.compactendscreen");
		if (manager->isCompactEndscreen) {
			manager->xPositionOneFourths = 240.f;
			manager->xPositionThreeFourths = 240.f;
			manager->yPositionOneFourths = 40.f;
			manager->yPositionThreeFourths = 115.f;
		}
	}
}