#include <Geode/modify/EndLevelLayer.hpp>
#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyEndLevelLayer, EndLevelLayer) {
	void onLastCheckpoint(cocos2d::CCObject* sender) {
		Manager::getSharedInstance()->isLevelComplete = false;
		if (auto pl = PlayLayer::get()) {
			// "this" keyword apparently necessary for instantcomplete keybind spammers like me -erymanthus | /u/raydeeux
			if (sender != nullptr) { this->getParent()->getParent()->removeFromParent(); }
			else { this->removeFromParent(); }
			pl->resetLevel();
		}
	}
	void customSetup() {
		EndLevelLayer::customSetup();
		auto manager = Manager::getSharedInstance();
		if (Utils::notQualified(this)) {
			return;
		}
		if (auto buttonMenu = getChildByIDRecursive("button-menu")) {
			auto lastCheckpoint = CCSprite::createWithSpriteFrameName("GJ_practiceBtn_001.png");
			lastCheckpoint->setID("button-sprite"_spr);
			auto checkpointButton = CCMenuItemSpriteExtra::create(lastCheckpoint, buttonMenu, menu_selector(MyEndLevelLayer::onLastCheckpoint));
			checkpointButton->setID("button"_spr);
			if (auto editButton = buttonMenu->getChildByIDRecursive("edit-button")) {
				auto retryButton = buttonMenu->getChildByIDRecursive("retry-button");
				auto exitButton = buttonMenu->getChildByIDRecursive("exit-button");
				if (!manager->isCompactEndscreen) {
					retryButton->setPosition({(-1 * manager->xPositionOneFourths), manager->yPositionOneFourths});
					exitButton->setPosition({manager->xPositionOneFourths, manager->yPositionOneFourths});
					editButton->setPosition({manager->xPositionThreeFourths, manager->yPositionOneFourths});
					checkpointButton->setPosition({-1 * (manager->xPositionThreeFourths), manager->yPositionOneFourths});
				} else {
					retryButton->setPosition({(manager->xPositionOneFourths), manager->yPositionThreeFourths});
					exitButton->setPosition({manager->xPositionOneFourths, (-1 * manager->yPositionThreeFourths)});
					editButton->setPosition({manager->xPositionThreeFourths, (-1 * manager->yPositionOneFourths)});
					checkpointButton->setPosition({manager->xPositionThreeFourths, manager->yPositionOneFourths});
				}
			} else if (buttonMenu->getChildByIDRecursive("retry-button") && buttonMenu->getChildByIDRecursive("exit-button")) {
				if (!manager->isCompactEndscreen) { checkpointButton->setPosition({0.f, manager->yPositionOneFourths}); }
				else {
					checkpointButton->setPosition({ manager->xPositionOneFourths, 0.f });
					buttonMenu->getChildByIDRecursive("retry-button")->setPosition({(manager->xPositionOneFourths), manager->yPositionThreeFourths});
					buttonMenu->getChildByIDRecursive("exit-button")->setPosition({manager->xPositionOneFourths, (-1 * manager->yPositionThreeFourths)});
				}
			} else {
				if (!manager->isCompactEndscreen) { checkpointButton->setPosition({manager->xPositionOneFourths, (-1.f * manager->yPositionOneFourths)}); }
				else { checkpointButton->setPosition({-90.f, -115.f}); }
			}
			buttonMenu->addChild(checkpointButton);
		}
	}
	#ifdef GEODE_IS_WINDOWS
	void keyDown(cocos2d::enumKeyCodes p0) {
		if (Utils::get("enabled") && Utils::get("spacebar") && p0 == enumKeyCodes::KEY_Space && this->getChildByIDRecursive("button"_spr) != nullptr && PlayLayer::get() != nullptr) {
			MyEndLevelLayer::onLastCheckpoint(nullptr);
		} else { EndLevelLayer::keyDown(p0); }
	}
	#endif
};
