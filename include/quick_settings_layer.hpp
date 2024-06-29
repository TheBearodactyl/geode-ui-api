#pragma once

#include "quick_settings.hpp"
#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp>

using namespace geode::prelude;

class QuickSettingsLayer : public Popup<> {
protected:
  std::vector<CCMenuItemToggler*> m_toggles;

  bool setup() override {
    auto winSize = CCDirector::sharedDirector()->getWinSize();

    this->setTitle("Select Quick Settings");

    auto settingsArray = this->createSettingsArray();
    auto listView = ListView::create(settingsArray, 30.f, 340.f, 200.f);

    auto listLayer = GJListLayer::create(listView, "Quick Settings", {191, 114, 62, 255}, 340.f, 200.f, 1);
    listLayer->setPosition(winSize.width / 2 - 170.f, winSize.height / 2 - 120.f);
    this->addChild(listLayer);

    return true;
  }

  CCArray* createSettingsArray() {
    auto manager = QuickSettingsManager::sharedManager();
    auto settings = manager->getSettings();
    auto array = CCArray::create();

    for (int i = 0; i < settings.size(); ++i) {
      auto& setting = settings[i];
      auto menu = CCMenu::create();

      auto label = CCLabelBMFont::create(setting.name.c_str(), "bigFont.fnt");
      label->setPosition(10.f, 15.f);
      label->setAnchorPoint({0.f, 0.5f});
      label->limitLabelWidth(200.f, 0.5f, 0.1f);
      menu->addChild(label);

      auto toggle = CCMenuItemToggler::createWithStandardSprites(this, menu_selector(QuickSettingsLayer::onToggle), 0.6f);
      toggle->setTag(i);
      toggle->setPosition(315.f, 15.f);
      toggle->toggle(manager->isSettingSelected(i));
      menu->addChild(toggle);
      m_toggles.push_back(toggle);

      if (!setting.isUnlocked) {
        label->setColor({150, 150, 150});
        toggle->setColor({150, 150, 150});
      }

      array->addObject(menu);
    }

    return array;
  }

public:
  static QuickSettingsLayer* create() {
    auto ret = new QuickSettingsLayer();
    if (ret && ret->init(440.f, 290.f)) {
      ret->autorelease();
      return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
  }

  void onToggle(CCObject* pSender) {
    auto toggle = static_cast<CCMenuItemToggler*>(pSender);
    auto manager = QuickSettingsManager::sharedManager();

    if (!manager->toggleSetting(toggle->getTag())) {
      toggle->toggle(false);
      if (manager->getSelectedCount() > manager->getMaxSettings()) {
        FLAlertLayer::create("Maximum Exceeded", "You've exceeded the maximum number of quick settings.", "OK")->show();
      } else if (manager->getSelectedCount() < manager->getMinSettings()) {
        FLAlertLayer::create("Minimum Not Met", "You haven't met the minimum number of quick settings.", "OK")->show();
      }
    }
  }

  void onClose(CCObject* pSender) override {
    auto manager = QuickSettingsManager::sharedManager();
    std::vector<int> selectedIndices;
    for (int i = 0; i < m_toggles.size(); ++i) {
      if (m_toggles[i]->isToggled()) {
        selectedIndices.push_back(i);
      }
    }
    manager->setSelectedIndices(selectedIndices);
    Popup::onClose(pSender);
  }
};
