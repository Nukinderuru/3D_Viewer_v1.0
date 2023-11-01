#ifndef MODELRENDERER_H
#define MODELRENDERER_H

#include <QColor>
#include <QDir>
#include <QFileDialog>
#include <QOpenGLWidget>

class ModelRenderer : public QOpenGLWidget {
  Q_OBJECT
 public:
  ModelRenderer(QWidget *parent = nullptr);
  ~ModelRenderer();
  void setFigureData(float *vertices, unsigned int *indices, float *edgesColors,
                     float *verticesColors, int count);
  void setProjectionMode(bool projectionMode);
  void setLineWidth(float lineWidth);
  void setPointSize(float pointSize);
  void setEdgesType(int edgesType);
  void setVerticesType(int verticesType);
  void setBackgroundColor(QColor backgroundColor);

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private:
  float *vertices;
  unsigned int *indices;
  float *edgesColors;
  float *verticesColors;
  int count;

  bool projectionMode;  // false - parallel, true - central
  float lineWidth;
  float pointSize;
  int edgesType;     // 0 - solid, 1 - dashed
  int verticesType;  // 0 - none, 1 - square, 2 - circle
  QColor backgroundColor;
};

#endif  // MODELRENDERER_H
