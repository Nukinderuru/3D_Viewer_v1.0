#include "affine.h"

void scale(float *M, int sizeM, float scaleFactorX, float scaleFactorY,
           float scaleFactorZ) {
  for (int i = 0; i < sizeM; i += 3) {
    M[i] *= scaleFactorX;
    M[i + 1] *= scaleFactorY;
    M[i + 2] *= scaleFactorZ;
  }
}
