#pragma once

#include <QString>

#include <nlohmann/json.hpp>

NLOHMANN_JSON_NAMESPACE_BEGIN
template<>
struct adl_serializer<QString>
{
  static void to_json(json& j, const QString& str) { j = str.toStdString(); };

  static void from_json(const json& j, QString& str)
  {
    str = QString::fromStdString(j.get<std::string>());
  };
};
NLOHMANN_JSON_NAMESPACE_END
