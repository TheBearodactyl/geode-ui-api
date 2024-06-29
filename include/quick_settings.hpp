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

  QuickSetting(std::string name, std::string category, std::function<bool()> isEnabled, std::function<void(bool)> setEnabled, bool isUnlocked) : name(std::move(name)), category(std::move(category)), isEnabled(std::move(isEnabled)), setEnabled(std::move(setEnabled)), isUnlocked(isUnlocked) {}
};

class QuickSettingsManager {
private:
  static QuickSettingsManager* s_instance;
  std::vector<QuickSetting> m_settings;
  std::vector<int> m_selectedIndices;
  const int m_maxSettings = 6;
  const int m_minSettings = 3;

  QuickSettingsManager() = default;

public:
  static QuickSettingsManager* sharedManager() {
    if (!s_instance) {
      s_instance = new QuickSettingsManager();
    }
    return s_instance;
  }

  void clearSettings() {
    m_settings.clear();
    m_selectedIndices.clear();
  }

  void addSetting(const QuickSetting& setting) {
    m_settings.push_back(setting);
  }

  const std::vector<QuickSetting>& getSettings() const {
    return m_settings;
  }

  std::vector<int> getSelectedIndices() const {
    return m_selectedIndices;
  }

  void setSelectedIndices(const std::vector<int>& selectedIndices) {
    m_selectedIndices = selectedIndices;
  }

  bool toggleSetting(int index) {
    auto it = std::find(m_selectedIndices.begin(), m_selectedIndices.end(), index);
    if (it != m_selectedIndices.end()) {
      m_selectedIndices.erase(it);
      return false;
    } else if (m_selectedIndices.size() < m_maxSettings) {
      m_selectedIndices.push_back(index);
      return true;
    }
    return false;
  }

  bool isSettingSelected(int index) const {
    return std::find(m_selectedIndices.begin(), m_selectedIndices.end(), index) != m_selectedIndices.end();
  }

  int getSelectedCount() const {
    return m_selectedIndices.size();
  }

  int getMaxSettings() const {
    return m_maxSettings;
  }

  int getMinSettings() const {
    return m_minSettings;
  }
};

QuickSettingsManager* QuickSettingsManager::s_instance = nullptr;
