#pragma once

#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp>
#include <quick_settings.hpp>

using namespace geode::prelude;

class QuickSettingsLayer : public Popup<> {
protected:
  std::vector<CCMenuItemToggler*> m_toggles;
  bool setup() override;
  CCArray* createSettingsArray();

public:
  static QuickSettingsLayer* create();
  void onToggle(CCObject* pSender);
  void onClose(CCObject* pSender) override;
};
