#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <modelrenderer.h>

#include <QColorDialog>
#include <QFile>
#include <QFileDialog>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPushButton>
#include <QRadioButton>
#include <QSlider>
#include <QSpinBox>
#include <QTimer>

#include "gifLibrary/QtGifImage/3rdParty/giflib/gif_lib.h"
#include "gifLibrary/QtGifImage/gifimage/qgifimage.h"

extern "C" {
#include "affine.h"
#include "parser.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void moveModel(int value);
  void rotateModel(int value);
  void scaleModel(int value);
  void changeProjectionMode();
  void changeEdgesColor(QColor c);
  void changeVerticesColor(QColor c);
  void changeEdgesThickness(int value);
  void changeVerticesThickness(int value);
  void changeEdgesType();
  void changeVerticesType();
  void changeBackgroundColor(QColor c);
  void clear();
  void openFile();
  void takeAScreenshot();
  void makeAGif();

 private:
  Ui::MainWindow *ui;
  ModelRenderer *modelView;
  ModelRenderer *axisView;

  QSlider *sliderMoveX;
  QSlider *sliderMoveY;
  QSlider *sliderMoveZ;
  QSlider *sliderRotateX;
  QSlider *sliderRotateY;
  QSlider *sliderRotateZ;
  QSlider *sliderScale;
  QSpinBox *spinMoveX;
  QSpinBox *spinMoveY;
  QSpinBox *spinMoveZ;
  QSpinBox *spinRotateX;
  QSpinBox *spinRotateY;
  QSpinBox *spinRotateZ;
  QSpinBox *spinScale;

  QPushButton *buttonReset;
  QRadioButton *buttonParallelProjection;
  QRadioButton *buttonCentralProjection;
  QAction *openFileAction;
  QAction *takeAScreenshotAction;
  QAction *makeAGifAction;
  QStatusBar *statusBar;
  QLabel *vInfo;
  QLabel *lInfo;
  QString filename;
  QColorDialog *edgesColorDialog;

  float *modelVerticesOrigin;
  float *modelVertices;
  int modelVerticesCount;
  unsigned int *modelIndices;
  int modelIndicesCount;
  float *modelEdgesColors;
  float *modelVerticesColors;

  float *axisVerticesOrigin;
  float *axisVertices;
  int axisVerticesCount;
  unsigned int *axisIndices;
  int axisIndicesCount;
  float *axisColors;

  float XRotation;
  float YRotation;
  float ZRotation;
  float XMove;
  float YMove;
  float ZMove;
  float scaleFactor;

  bool projectionMode;  // false - parallel, true - central

  int edgesType;
  QColor edgesColor;
  int edgesThickness;
  int verticesType;
  QColor verticesColor;
  int verticesThickness;
  QColor backgroundColor;

  QPoint mousePressedPos;
  QPoint mouseMovedPos;

  QTimer timerUi;
  QString gifFileName;
  QTimer *timerGIF;  // идентификатор таймера
  int frame;
  QGifImage *gif;
  QFile *ptrSaveGif;

  void copyVertexArray(float *src, float *dst, int size);
  void normalizeModel();
  void updateModelAndAxis();
  bool eventFilter(QObject *watched, QEvent *event);
  void setInfo();
  void startTimerGif();
  void recordGif();
  void loadSettings();
  void uploadSettings();
};
#endif  // MAINWINDOW_H
