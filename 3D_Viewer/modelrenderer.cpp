#include "modelrenderer.h"

#include <QDebug>

ModelRenderer::ModelRenderer(QWidget *parent) : QOpenGLWidget(parent) {
  vertices = nullptr;
  indices = nullptr;
  edgesColors = nullptr;
  verticesColors = nullptr;
  count = 0;
  projectionMode = false;
  lineWidth = 1.0f;
  pointSize = 1.0f;
  backgroundColor = QColor(0, 0, 0);
  edgesType = 0;
  verticesType = 0;
}

ModelRenderer::~ModelRenderer() {}

void ModelRenderer::setFigureData(float *vertices, unsigned int *indices,
                                  float *edgesColors, float *verticesColors,
                                  int count) {
  this->vertices = vertices;
  this->indices = indices;
  this->edgesColors = edgesColors;
  this->verticesColors = verticesColors;
  this->count = count;
}

void ModelRenderer::setProjectionMode(bool projectionMode) {
  this->projectionMode = projectionMode;
}

void ModelRenderer::setLineWidth(float lineWidth) {
  this->lineWidth = lineWidth;
}

void ModelRenderer::setPointSize(float pointSize) {
  this->pointSize = pointSize;
}

void ModelRenderer::setEdgesType(int edgesType) { this->edgesType = edgesType; }

void ModelRenderer::setVerticesType(int verticesType) {
  this->verticesType = verticesType;
}

void ModelRenderer::setBackgroundColor(QColor backgroundColor) {
  this->backgroundColor = backgroundColor;
}

void ModelRenderer::initializeGL() { glEnable(GL_DEPTH_TEST); }

void ModelRenderer::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void ModelRenderer::paintGL() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (projectionMode) {
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);
  }
  glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
               backgroundColor.blueF(), 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glLineWidth(lineWidth);
  glPointSize(pointSize);

  if (edgesType) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xAAAA);
  }
  if (verticesType == 2) {
    glEnable(GL_POINT_SMOOTH);
  }

  // draw edges
  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glEnableClientState(GL_VERTEX_ARRAY);
  glColorPointer(3, GL_FLOAT, 0, edgesColors);
  glEnableClientState(GL_COLOR_ARRAY);
  glDrawElements(GL_LINES, count, GL_UNSIGNED_INT, indices);

  // draw vertices
  if (verticesType) {
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, verticesColors);
    glEnableClientState(GL_COLOR_ARRAY);
    glDrawElements(GL_POINTS, count, GL_UNSIGNED_INT, indices);
  }

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);

  glDisable(GL_LINE_STIPPLE);
  glDisable(GL_POINT_SMOOTH);
  glDisable(GL_BLEND);
}
