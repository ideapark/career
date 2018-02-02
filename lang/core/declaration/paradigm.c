#include <stdio.h>

int main(void)
{
  int iVar1, iVar2 = 10;
  static char msg[] = "Hello, world!";

  extern volatile short status;

  enum { OFF, ON } toggle = ON;

  struct CharColor { unsigned fg:4, bg:3, bl:1; };
  struct CharColor attribute = { 12, 1, 0 };
  struct CharColor charArray[100];
  struct CharColor *pCharColor = charArray;

  float x, *flPtrArray[10] = { &x };

  const int limit = 10000;                   // integer constant
  typedef struct { double x, y, r; } Circle; // struct type
  const Circle unit_circle = { 0, 0, 1 };    // constant circle
  const float v[] = { 1.0F, 0.5F, 0.25F };   // constant float array
  volatile short * restrict vsPtr;           // pointing to volatile short

  return 0;
}
