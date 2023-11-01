#include "affine.h"

void rotateX(float *M, int sizeM, float angle) {
  float angleRad = angle * (M_PI / 180);
  float cosTheta = cos(angleRad);
  float sinTheta = sin(angleRad);

  float *resM = (float *)calloc(sizeM, sizeof(float));
  for (int i = 0; i < sizeM; i++) {
    resM[i] = M[i];
  }
  for (int i = 0; i < sizeM; i += 3) {
    resM[i] = M[i];
    resM[i + 1] = M[i + 1] * cosTheta - M[i + 2] * sinTheta;
    resM[i + 2] = M[i + 1] * sinTheta + M[i + 2] * cosTheta;
  }
  for (int i = 0; i < sizeM; i++) {
    M[i] = resM[i];
  }
  free(resM);
}

void rotateY(float *M, int sizeM, float angle) {
  float angleRad = angle * (M_PI / 180);
  float cosTheta = cos(angleRad);
  float sinTheta = sin(angleRad);

  float *resM = (float *)calloc(sizeM, sizeof(float));
  for (int i = 0; i < sizeM; i++) {
    resM[i] = M[i];
  }
  for (int i = 0; i < sizeM; i += 3) {
    resM[i] = M[i] * cosTheta + M[i + 2] * sinTheta;
    resM[i + 1] = M[i + 1];
    resM[i + 2] = M[i] * -sinTheta + M[i + 2] * cosTheta;
  }
  for (int i = 0; i < sizeM; i++) {
    M[i] = resM[i];
  }
  free(resM);
}

void rotateZ(float *M, int sizeM, float angle) {
  float angleRad = angle * (M_PI / 180);
  float cosTheta = cos(angleRad);
  float sinTheta = sin(angleRad);

  float *resM = (float *)calloc(sizeM, sizeof(float));
  for (int i = 0; i < sizeM; i++) {
    resM[i] = M[i];
  }
  for (int i = 0; i < sizeM; i += 3) {
    resM[i] = M[i] * cosTheta - M[i + 1] * sinTheta;
    resM[i + 1] = M[i] * sinTheta + M[i + 1] * cosTheta;
    resM[i + 2] = M[i + 2];
  }
  for (int i = 0; i < sizeM; i++) {
    M[i] = resM[i];
  }
  free(resM);
}
