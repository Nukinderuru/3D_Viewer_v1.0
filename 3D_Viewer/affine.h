#ifndef AFFINE_H
#define AFFINE_H
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <stdlib.h>

void translate(float *M, int sizeM, float xMov, float yMov, float zMov);

void scale(float *M, int sizeM, float scaleFactorX, float scaleFactorY,
           float scaleFactorZ);

void rotateX(float *M, int sizeM, float angle);
void rotateY(float *M, int sizeM, float angle);
void rotateZ(float *M, int sizeM, float angle);

#endif  // AFFINE_H
