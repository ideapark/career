/*
 * Copyright (C) Zhou Peng <lockrecv@qq.com>
 */
#ifndef CALLGRAPH_UTILITY_H
#define CALLGRAPH_UTILITY_H

#include <string>
#include <sstream>

template <typename T>
bool lexical_cast(const std::string &s, T &value)
{
  T temp;
  std::stringstream stream(s);

  stream >> temp;
  if (stream.fail())
    return false;

  value = temp;
  return true;
}

inline std::string get_color(float ratio)
{
  static const float COLOR_THRESHOLD_RED    = 1;
  static const float COLOR_THRESHOLD_YELLOW = 0.1;
  static const std::string COLOR_RED    = "red";
  static const std::string COLOR_YELLOW = "yellow";
  static const std::string COLOR_WHITE  = "white";

  if (ratio >= COLOR_THRESHOLD_RED)
    return COLOR_RED;
  else if (ratio >= COLOR_THRESHOLD_YELLOW)
    return COLOR_YELLOW;
  else
    return COLOR_WHITE;
}

inline std::string dot_length_limited(const std::string &name)
{
  static const int DOT_NAME_LENGTH_LIMIT = 100;
  static const std::string DOT_NAME_ELLIPSIS = "...";

  if (name.size() >= DOT_NAME_LENGTH_LIMIT)
    return name.substr(0, DOT_NAME_LENGTH_LIMIT) + DOT_NAME_ELLIPSIS;
  else
    return name;
}

#endif /* CALLGRAPH_UTILITY_H */
