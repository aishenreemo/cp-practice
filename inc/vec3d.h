#ifndef VEC3D_H
#define VEC3D_H

#include <math.h>

#define VEC3D_DOT(vec_a, vec_b) (vec_a[0] * vec_b[0] + vec_a[1] * vec_b[1] + vec_a[2] * vec_b[2])
#define VEC3D_LEN(vec) sqrt(VEC3D_DOT(vec, vec))
#define VEC3D_MUL(k, vec)                                                                          \
	{ k * vec[0], k * vec[1], k * vec[2] }
#define VEC3D_ADD(vec_a, vec_b)                                                                    \
	{ vec_a[0] + vec_b[0], vec_a[1] + vec_b[1], vec_a[2] + vec_b[2] }
#define VEC3D_SUB(vec_a, vec_b)                                                                    \
	{ vec_a[0] - vec_b[0], vec_a[1] - vec_b[1], vec_a[2] - vec_b[2] }

#endif // VEC3D_H
