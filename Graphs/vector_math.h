#pragma once
#ifndef VECTOR_MATH_H
#define VECTOR_MATH_H
struct {
	int x;
	int y;
} typedef Vector2i;

struct {
	double x;
	double y;
} typedef Vector2d;



Vector2d intersect_lines(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
#endif // !VECTOR_MATH_H
