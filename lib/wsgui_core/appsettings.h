#pragma once

#include <chrono>
#include <string>

namespace wsgui::core
{

// plain aggregate so glaze can reflect its members; keep fields as plain
// ints/strings for trivial (de)serialization and add std::chrono accessors
// for C++ consumers
struct AppSettings
{
  // Panomax camera id; <= 0 means "not configured" (there is deliberately no
  // default camera)
  int panomaxCamId = 0;
  std::string panomaxResolution = "default";
  // used when panomaxResolution is not offered by the camera
  std::string panomaxFallbackResolution = "default";
  int updateIntervalSeconds = 60;

  std::chrono::seconds updateInterval() const
  {
    return std::chrono::seconds(updateIntervalSeconds);
  }
};

} // namespace wsgui::core
