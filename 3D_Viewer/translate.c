#include "affine.h"

void translate(float *M, int sizeM, float xMov, float yMov, float zMov) {
  for (int i = 0; i < sizeM; i += 3) {
    M[i] += xMov;
    M[i + 1] += yMov;
    M[i + 2] += zMov;
  }
}
