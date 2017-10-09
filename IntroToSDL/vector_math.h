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

Vector2i vector_from_points(Vector2i v1, Vector2i v2);

int scalar_product(Vector2i a, Vector2i b);

double length(Vector2i a);

Vector2d multiply_with_scalar(double scalar, Vector2i vector);

Vector2d orthogonal_projection(Vector2i a, Vector2i b);

Vector2d intersect_lines(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
#endif // !VECTOR_MATH_H
