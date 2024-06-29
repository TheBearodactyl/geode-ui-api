#include <quick_settings.hpp>

QuickSettingsManager* QuickSettingsManager::s_instance = nullptr;

QuickSettingsManager* QuickSettingsManager::sharedManager() {
  if (!s_instance) {
    s_instance = new QuickSettingsManager();
  }
  return s_instance;
}

void QuickSettingsManager::addSetting(const QuickSetting& setting) {
  m_settings.push_back(setting);
}

const std::vector<QuickSetting>& QuickSettingsManager::getSettings() const {
  return m_settings;
}

std::vector<size_t> QuickSettingsManager::getSelectedIndices() const {
  return m_selectedIndices;
}

void QuickSettingsManager::setSelectedIndices(const std::vector<size_t>& selectedIndices) {
  m_selectedIndices = selectedIndices;
}

bool QuickSettingsManager::toggleSetting(size_t index) {
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

bool QuickSettingsManager::isSettingSelected(size_t index) const {
  return std::find(m_selectedIndices.begin(), m_selectedIndices.end(), index) != m_selectedIndices.end();
}

size_t QuickSettingsManager::getSelectedCount() const {
  return m_selectedIndices.size();
}

size_t QuickSettingsManager::getMaxSettings() const {
  return m_maxSettings;
}

size_t QuickSettingsManager::getMinSettings() const {
  return m_minSettings;
}
