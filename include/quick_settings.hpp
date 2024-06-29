#pragma once

#include <functional>
#include <string>
#include <vector>

struct QuickSetting {
  std::string name;
  std::string category;
  std::function<bool()> isEnabled;
  std::function<void(bool)> setEnabled;
  bool isUnlocked;
};

class QuickSettingsManager {
private:
  static QuickSettingsManager* s_instance;
  std::vector<QuickSetting> m_settings;
  std::vector<size_t> m_selectedIndices;
  const size_t m_maxSettings = 6;
  const size_t m_minSettings = 3;

  QuickSettingsManager() = default;

public:
  static QuickSettingsManager* sharedManager();

  void addSetting(const QuickSetting& setting);
  const std::vector<QuickSetting>& getSettings() const;
  std::vector<size_t> getSelectedIndices() const;
  void setSelectedIndices(const std::vector<size_t>& selectedIndices);
  bool toggleSetting(size_t index);
  bool isSettingSelected(size_t index) const;
  size_t getSelectedCount() const;
  size_t getMaxSettings() const;
  size_t getMinSettings() const;
};
