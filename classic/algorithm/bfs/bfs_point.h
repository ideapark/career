/*
 * Copyright (C) Zhou Peng <lockrecv@gmail.com>
 */

#ifndef BFS_POINT_H
#define BFS_POINT_H

#include <iostream>

struct point {
  short x;
  short y;
};

inline int UUID(const struct point &p)
{
  int uuid = p.y;

  return (uuid << 16 | p.x);
}

inline struct point POINT(int uuid)
{
  struct point p;

  p.y = uuid >> 16;
  p.x = uuid | (~0 << 16);

  return p;
}

inline struct point UP(const struct point &p)
{
  struct point up;

  up.x = p.x;
  up.y = p.y - 1;

  return up;
}

inline struct point DOWN(const struct point &p)
{
  struct point down;

  down.x = p.x;
  down.y = p.y + 1;

  return down;
}

inline struct point LEFT(const struct point &p)
{
  struct point left;

  left.x = p.x - 1;
  left.y = p.y;

  return left;
}

inline struct point RIGHT(const struct point &p)
{
  struct point right;

  right.x = p.x + 1;
  right.y = p.y;

  return right;
}

#endif /* BFS_POINT_H */
