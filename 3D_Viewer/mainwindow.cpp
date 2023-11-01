#include "mainwindow.h"

#include <QDebug>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // initialize ui fields
  modelView = ui->model;
  axisView = ui->axis;

  sliderMoveX = ui->horizontalSliderMoveX;
  sliderMoveY = ui->horizontalSliderMoveY;
  sliderMoveZ = ui->horizontalSliderMoveZ;
  sliderRotateX = ui->horizontalSliderRotateX;
  sliderRotateY = ui->horizontalSliderRotateY;
  sliderRotateZ = ui->horizontalSliderRotateZ;
  sliderScale = ui->horizontalSliderScale;
  spinMoveX = ui->spinBoxMoveX;
  spinMoveY = ui->spinBoxMoveY;
  spinMoveZ = ui->spinBoxMoveZ;
  spinRotateX = ui->spinBoxRotateX;
  spinRotateY = ui->spinBoxRotateY;
  spinRotateZ = ui->spinBoxRotateZ;
  spinScale = ui->spinBoxScale;

  buttonReset = ui->pushButtonReset;
  buttonParallelProjection = ui->radioButtonParallelProjection;
  buttonCentralProjection = ui->radioButtonCentralProjection;
  openFileAction = ui->actionOpen_file;
  takeAScreenshotAction = ui->actionTake_a_screenshot;
  makeAGifAction = ui->actionMake_a_GIF;
  statusBar = ui->statusBar;

  // set edges menu
  edgesColorDialog = new QColorDialog();
  edgesColorDialog->setOption(QColorDialog::NoButtons, true);
  edgesColorDialog->setOption(QColorDialog::DontUseNativeDialog, true);
  QGridLayout *edgesColorDialogLayout = new QGridLayout();
  edgesColorDialogLayout->addWidget(edgesColorDialog);
  ui->edgesColor->setLayout(edgesColorDialogLayout);
  QSlider *edgesThicknessSlider = new QSlider();
  edgesThicknessSlider->setMinimum(0);
  edgesThicknessSlider->setMaximum(10);
  edgesThicknessSlider->setOrientation(Qt::Horizontal);
  edgesThicknessSlider->setSizePolicy(QSizePolicy::Minimum,
                                      QSizePolicy::Minimum);
  edgesThicknessSlider->setPageStep(1);
  QGridLayout *edgesThicknessSliderLayout = new QGridLayout();
  edgesThicknessSliderLayout->addWidget(edgesThicknessSlider);
  ui->edgesThickness->setLayout(edgesThicknessSliderLayout);
  vInfo = new QLabel();
  lInfo = new QLabel;
  statusBar->addWidget(vInfo);
  statusBar->addWidget(lInfo);

  // set vertices menu
  QColorDialog *verticesColorDialog = new QColorDialog();
  verticesColorDialog->setOption(QColorDialog::NoButtons, true);
  verticesColorDialog->setOption(QColorDialog::DontUseNativeDialog, true);
  QGridLayout *verticesColorDialogLayout = new QGridLayout();
  verticesColorDialogLayout->addWidget(verticesColorDialog);
  ui->verticesColor->setLayout(verticesColorDialogLayout);
  QSlider *verticesThicknessSlider = new QSlider();
  verticesThicknessSlider->setMinimum(0);
  verticesThicknessSlider->setMaximum(10);
  verticesThicknessSlider->setOrientation(Qt::Horizontal);
  verticesThicknessSlider->setSizePolicy(QSizePolicy::Minimum,
                                         QSizePolicy::Minimum);
  verticesThicknessSlider->setPageStep(1);
  QGridLayout *verticesThicknessSliderLayout = new QGridLayout();
  verticesThicknessSliderLayout->addWidget(verticesThicknessSlider);
  ui->verticesThickness->setLayout(verticesThicknessSliderLayout);

  // set background menu
  QColorDialog *backgroundColorDialog = new QColorDialog();
  backgroundColorDialog->setOption(QColorDialog::NoButtons, true);
  backgroundColorDialog->setOption(QColorDialog::DontUseNativeDialog, true);
  QGridLayout *backgroundColorDialogLayout = new QGridLayout();
  backgroundColorDialogLayout->addWidget(backgroundColorDialog);
  ui->backgroundColor->setLayout(backgroundColorDialogLayout);

  XRotation = 0;
  YRotation = 0;
  ZRotation = 0;
  XMove = 0;
  YMove = 0;
  ZMove = 0;
  scaleFactor = 1;
  projectionMode = false;

  axisVerticesCount = 18;
  axisVerticesOrigin = new float[18]{
      0,   0,   0,   // 0
      0.5, 0,   0,   // 1
      0,   0,   0,   // 2
      0,   0.5, 0,   // 3
      0,   0,   0,   // 4
      0,   0,   0.5  // 5
  };
  axisIndicesCount = 20;
  axisIndices = new unsigned int[20]{
      4, 5, 5, 4, 0, 1, 1, 0, 3, 2, 2, 3, 0, 4, 4, 0, 0, 3, 3, 0,
  };
  axisVertices = new float[axisVerticesCount];
  copyVertexArray(axisVerticesOrigin, axisVertices, axisVerticesCount);
  axisColors =
      new float[18]{1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1};
  axisView->setFigureData(axisVertices, axisIndices, axisColors, axisColors,
                          axisIndicesCount);

  modelVerticesCount = 0;
  modelIndicesCount = 0;
  modelVerticesOrigin = nullptr;
  modelVertices = nullptr;
  modelIndices = nullptr;
  modelEdgesColors = nullptr;
  modelVerticesColors = nullptr;
  modelView->setFigureData(modelVertices, modelIndices, modelEdgesColors,
                           modelVerticesColors, modelIndicesCount);

  edgesType = 0;
  edgesColor = QColor(255, 255, 255);
  edgesThickness = 0;
  verticesType = 0;
  verticesColor = QColor(255, 255, 255);
  verticesThickness = 1;
  backgroundColor = QColor(0, 0, 0);

  mousePressedPos = QPoint(0, 0);
  mouseMovedPos = QPoint(0, 0);

  modelView->installEventFilter(this);

  // connect slots & signals
  connect(sliderMoveX, SIGNAL(valueChanged(int)), this, SLOT(moveModel(int)));
  connect(sliderMoveY, SIGNAL(valueChanged(int)), this, SLOT(moveModel(int)));
  connect(sliderMoveZ, SIGNAL(valueChanged(int)), this, SLOT(moveModel(int)));
  connect(spinMoveX, SIGNAL(valueChanged(int)), this, SLOT(moveModel(int)));
  connect(spinMoveY, SIGNAL(valueChanged(int)), this, SLOT(moveModel(int)));
  connect(spinMoveZ, SIGNAL(valueChanged(int)), this, SLOT(moveModel(int)));

  connect(sliderRotateX, SIGNAL(valueChanged(int)), this,
          SLOT(rotateModel(int)));
  connect(sliderRotateY, SIGNAL(valueChanged(int)), this,
          SLOT(rotateModel(int)));
  connect(sliderRotateZ, SIGNAL(valueChanged(int)), this,
          SLOT(rotateModel(int)));
  connect(spinRotateX, SIGNAL(valueChanged(int)), this, SLOT(rotateModel(int)));
  connect(spinRotateY, SIGNAL(valueChanged(int)), this, SLOT(rotateModel(int)));
  connect(spinRotateZ, SIGNAL(valueChanged(int)), this, SLOT(rotateModel(int)));

  connect(sliderScale, SIGNAL(valueChanged(int)), this, SLOT(scaleModel(int)));
  connect(spinScale, SIGNAL(valueChanged(int)), this, SLOT(scaleModel(int)));

  connect(buttonReset, SIGNAL(clicked(bool)), this, SLOT(clear()));

  connect(buttonParallelProjection, SIGNAL(clicked(bool)), this,
          SLOT(changeProjectionMode()));
  connect(buttonCentralProjection, SIGNAL(clicked(bool)), this,
          SLOT(changeProjectionMode()));

  connect(openFileAction, SIGNAL(triggered(bool)), this, SLOT(openFile()));
  connect(takeAScreenshotAction, SIGNAL(triggered(bool)), this,
          SLOT(takeAScreenshot()));
  connect(makeAGifAction, SIGNAL(triggered(bool)), this, SLOT(makeAGif()));
  connect(edgesColorDialog, SIGNAL(currentColorChanged(QColor)), this,
          SLOT(changeEdgesColor(QColor)));
  connect(verticesColorDialog, SIGNAL(currentColorChanged(QColor)), this,
          SLOT(changeVerticesColor(QColor)));
  connect(edgesThicknessSlider, SIGNAL(valueChanged(int)), this,
          SLOT(changeEdgesThickness(int)));
  connect(verticesThicknessSlider, SIGNAL(valueChanged(int)), this,
          SLOT(changeVerticesThickness(int)));

  connect(ui->actionSolid, SIGNAL(triggered(bool)), this,
          SLOT(changeEdgesType()));
  connect(ui->actionDashed, SIGNAL(triggered(bool)), this,
          SLOT(changeEdgesType()));

  connect(ui->actionNone, SIGNAL(triggered(bool)), this,
          SLOT(changeVerticesType()));
  connect(ui->actionSquare, SIGNAL(triggered(bool)), this,
          SLOT(changeVerticesType()));
  connect(ui->actionCircle, SIGNAL(triggered(bool)), this,
          SLOT(changeVerticesType()));
  connect(backgroundColorDialog, SIGNAL(currentColorChanged(QColor)), this,
          SLOT(changeBackgroundColor(QColor)));

  loadSettings();
}

MainWindow::~MainWindow() {
  uploadSettings();

  delete ui;

  if (modelVerticesOrigin) {
    delete[] modelVerticesOrigin;
    delete[] modelVertices;
    delete[] modelIndices;
    delete[] modelEdgesColors;
  }
  if (modelVerticesColors) {
    delete[] modelVerticesColors;
  }

  delete[] axisVerticesOrigin;
  delete[] axisVertices;
  delete[] axisIndices;
  delete[] axisColors;
}

void MainWindow::copyVertexArray(float *src, float *dst, int size) {
  for (int i = 0; i < size; i++) {
    dst[i] = src[i];
  }
}

void MainWindow::normalizeModel() {
  float maxCord = 0;
  for (int i = 0; i < modelVerticesCount; i++) {
    if (fabs(maxCord) < fabs(modelVerticesOrigin[i])) {
      maxCord = modelVerticesOrigin[i];
    }
  }
  for (int i = 0; i < modelVerticesCount; i++) {
    modelVerticesOrigin[i] /= maxCord * 1.1;
  }
  float maxX = -1e18;
  float maxY = -1e18;
  float maxZ = -1e18;
  float minX = 1e18;
  float minY = 1e18;
  float minZ = 1e18;

  for (int i = 0; i < modelVerticesCount; i += 3) {
    maxX = fmax(maxX, modelVerticesOrigin[i]);
    minX = fmin(minX, modelVerticesOrigin[i]);

    maxY = fmax(maxY, modelVerticesOrigin[i + 1]);
    minY = fmin(minY, modelVerticesOrigin[i + 1]);

    maxZ = fmax(maxZ, modelVerticesOrigin[i + 2]);
    minZ = fmin(minZ, modelVerticesOrigin[i + 2]);
  }
  float offsetX = -(maxX + minX) / 2;
  float offsetY = -(maxY + minY) / 2;
  float offsetZ = -(maxZ + minZ) / 2;

  for (int i = 0; i < modelVerticesCount; i += 3) {
    modelVerticesOrigin[i] += offsetX;
    modelVerticesOrigin[i + 1] += offsetY;
    modelVerticesOrigin[i + 2] += offsetZ;
  }
}

void MainWindow::moveModel(int value) {
  if (sender() == sliderMoveX || sender() == spinMoveX) {
    XMove = -value / 100.0;
    sliderMoveX->setValue(value);
    spinMoveX->setValue(value);
  } else if (sender() == sliderMoveY || sender() == spinMoveY) {
    YMove = -value / 100.0;
    sliderMoveY->setValue(value);
    spinMoveY->setValue(value);
  } else if (sender() == sliderMoveZ || sender() == spinMoveZ) {
    ZMove = -value / 100.0;
    sliderMoveZ->setValue(value);
    spinMoveZ->setValue(value);
  }
  updateModelAndAxis();
}

void MainWindow::rotateModel(int value) {
  if (sender() == sliderRotateX || sender() == spinRotateX) {
    XRotation = value;
    sliderRotateX->setValue(value);
    spinRotateX->setValue(value);
  } else if (sender() == sliderRotateY || sender() == spinRotateY) {
    YRotation = value;
    sliderRotateY->setValue(value);
    spinRotateY->setValue(value);
  } else if (sender() == sliderRotateZ || sender() == spinRotateZ) {
    ZRotation = value;
    sliderRotateZ->setValue(value);
    spinRotateZ->setValue(value);
  }
  updateModelAndAxis();
}

void MainWindow::updateModelAndAxis() {
  XRotation -= 360 * (XRotation > 180);
  XRotation += 360 * (XRotation < -180);
  YRotation -= 360 * (YRotation > 180);
  YRotation += 360 * (YRotation < -180);
  ZRotation -= 360 * (ZRotation > 180);
  ZRotation += 360 * (ZRotation < -180);

  // copy array's origins
  copyVertexArray(modelVerticesOrigin, modelVertices, modelVerticesCount);
  copyVertexArray(axisVerticesOrigin, axisVertices, axisVerticesCount);

  // scale model & axis
  scale(modelVertices, modelVerticesCount, scaleFactor, scaleFactor,
        scaleFactor);
  scale(axisVertices, axisVerticesCount, scaleFactor, scaleFactor, scaleFactor);

  // move model (in relative cords)
  float mvX = XMove * axisVertices[3] + YMove * axisVertices[4] +
              ZMove * axisVertices[5];
  float mvY = XMove * axisVertices[9] + YMove * axisVertices[10] +
              ZMove * axisVertices[11];
  float mvZ = XMove * axisVertices[15] + YMove * axisVertices[16] +
              ZMove * axisVertices[17];
  translate(modelVertices, modelVerticesCount, -mvX, -mvY, -mvZ);

  // rotate model & axis
  rotateX(modelVertices, modelVerticesCount, XRotation);
  rotateY(modelVertices, modelVerticesCount, YRotation);
  rotateZ(modelVertices, modelVerticesCount, ZRotation);
  rotateX(axisVertices, axisVerticesCount, XRotation);
  rotateY(axisVertices, axisVerticesCount, YRotation);
  rotateZ(axisVertices, axisVerticesCount, ZRotation);

  //  if projection is central
  if (projectionMode) {
    scale(modelVertices, modelVerticesCount, 2, 2, 2);
    for (int i = 2; i < modelVerticesCount; i += 3) {
      modelVertices[i] -= 2.25;
    }
  }
  modelView->update();
  axisView->update();
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
  if (event->type() == QEvent::MouseButtonPress) {
    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    mousePressedPos = mouseEvent->pos();
  } else if (event->type() == QEvent::MouseMove) {
    if (!mousePressedPos.isNull()) {
      QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
      mouseMovedPos = mouseEvent->pos();
      XRotation += 1 / M_PI * (mouseMovedPos.y() - mousePressedPos.y()) * 1.8;
      YRotation += 1 / M_PI * (mouseMovedPos.x() - mousePressedPos.x()) * 1.8;
      sliderRotateX->setValue(XRotation);
      sliderRotateY->setValue(YRotation);
      emit sliderRotateX->valueChanged(XRotation);
      emit sliderRotateY->valueChanged(YRotation);
      mousePressedPos = mouseMovedPos;
    }
  } else if (event->type() == QEvent::MouseButtonRelease) {
    mousePressedPos.setX(0);
    mousePressedPos.setY(0);
  } else if (event->type() == QEvent::Wheel) {
    QWheelEvent *wheelEvent = static_cast<QWheelEvent *>(event);
    int newValue =
        sliderScale->value() + (wheelEvent->angleDelta().y()) / 120 * 2;
    if (abs(newValue) > 100) {
      newValue = sliderScale->value() + (wheelEvent->angleDelta().y()) / 120;
    }
    if (abs(newValue) <= 100) {
      sliderScale->setValue(newValue);
      emit sliderScale->valueChanged(newValue);
    }
  }
  return QMainWindow::eventFilter(watched, event);
}

void MainWindow::setInfo() {
  setWindowTitle(filename);
  QString verticesInfo =
      "Number of vertices: " + QString::number(modelVerticesCount / 3);
  QString linksInfo =
      "Number of links: " + QString::number(modelIndicesCount / 4);
  vInfo->setText(verticesInfo);
  lInfo->setText(linksInfo);
}

void MainWindow::startTimerGif() {
  gif = new QGifImage(QSize(640, 480));
  timerGIF = new QTimer(this);
  connect(timerGIF, &QTimer::timeout, this, &MainWindow::recordGif);
  timerGIF->start(100);
  frame = 0;
}

void MainWindow::recordGif() {
  const QRect rect(0, 100, 640, 480);
  QPixmap pixmap = modelView->grab(rect);

  //    qDebug() << "pixmap = " << pixmap;

  QImage myImage = pixmap.toImage();
  frame++;
  gif->addFrame(myImage, 100);  // Число - это задержка
  if (frame >= 50) {
    timerGIF->stop();
    gif->save(ptrSaveGif);
    ptrSaveGif->close();
    delete ptrSaveGif;
    ptrSaveGif = nullptr;
    delete gif;
    gif = nullptr;
    QMessageBox::about(this, "Status", "GIF saved");
  }
}

void MainWindow::loadSettings() {
  // read settings from file (if exists)
  QFile settingsFile(QCoreApplication::applicationDirPath() + "/settings.dat");
  if (settingsFile.open(QIODevice::ReadOnly)) {
    QDataStream in(&settingsFile);
    in >> edgesColor >> edgesThickness >> edgesType >> verticesColor >>
        verticesThickness >> verticesType >> backgroundColor;
  }
  settingsFile.close();

  changeEdgesColor(edgesColor);
  changeEdgesThickness(edgesThickness);
  changeEdgesType();

  changeVerticesColor(verticesColor);
  changeVerticesThickness(verticesThickness);
  changeVerticesType();

  changeBackgroundColor(backgroundColor);
}

void MainWindow::uploadSettings() {
  // write settings to file
  QFile settingsFile(QCoreApplication::applicationDirPath() + "/settings.dat");
  if (settingsFile.open(QIODevice::WriteOnly)) {
    QDataStream out(&settingsFile);
    out << edgesColor << edgesThickness << edgesType << verticesColor
        << verticesThickness << verticesType << backgroundColor;
  }
  settingsFile.close();
}

void MainWindow::takeAScreenshot() {
  QImage img = modelView->grabFramebuffer();
  QString screenshot = QFileDialog::getSaveFileName(
      this, tr("Save File"), QDir::homePath(), tr("Images (*.jpeg *.bmp)"));
  if (!screenshot.isNull()) {
    img.save(screenshot);
  }
}

void MainWindow::makeAGif() {
  QString filter = "*.gif";
  gifFileName = "/0";
  gifFileName =
      QFileDialog::getSaveFileName(this, "Save GIF", QDir::homePath(), filter);

  ptrSaveGif = new QFile(gifFileName);
  if (!ptrSaveGif->open(QIODevice::WriteOnly)) {
    QMessageBox::critical(this, "Warning", "Failed to write file");
  } else {
    startTimerGif();
  }
}

void MainWindow::scaleModel(int value) {
  scaleFactor = 1 + value / 101.0;
  sliderScale->setValue(value);
  spinScale->setValue(value);
  updateModelAndAxis();
}

void MainWindow::changeProjectionMode() {
  projectionMode = (sender() == buttonCentralProjection);
  modelView->setProjectionMode(projectionMode);
  updateModelAndAxis();
}

void MainWindow::changeEdgesColor(QColor c) {
  edgesColor = c;
  for (int i = 0; i < modelVerticesCount; i += 3) {
    modelEdgesColors[i] = c.redF();
    modelEdgesColors[i + 1] = c.greenF();
    modelEdgesColors[i + 2] = c.blueF();
  }
  updateModelAndAxis();
}

void MainWindow::changeVerticesColor(QColor c) {
  verticesColor = c;
  for (int i = 0; i < modelVerticesCount; i += 3) {
    modelVerticesColors[i] = c.redF();
    modelVerticesColors[i + 1] = c.greenF();
    modelVerticesColors[i + 2] = c.blueF();
  }
  updateModelAndAxis();
}

void MainWindow::changeEdgesThickness(int value) {
  edgesThickness = value;
  modelView->setLineWidth(value);
  updateModelAndAxis();
}

void MainWindow::changeVerticesThickness(int value) {
  verticesThickness = value;
  modelView->setPointSize(value);
  updateModelAndAxis();
}

void MainWindow::changeEdgesType() {
  if (sender() == ui->actionSolid) {
    edgesType = 0;
  } else if (sender() == ui->actionDashed) {
    edgesType = 1;
  }
  modelView->setEdgesType(edgesType);
  updateModelAndAxis();
}

void MainWindow::changeVerticesType() {
  if (sender() == ui->actionNone) {
    verticesType = 0;
  } else if (sender() == ui->actionSquare) {
    verticesType = 1;
  } else if (sender() == ui->actionCircle) {
    verticesType = 2;
  }
  modelView->setVerticesType(verticesType);
  updateModelAndAxis();
}

void MainWindow::changeBackgroundColor(QColor c) {
  backgroundColor = c;
  modelView->setBackgroundColor(backgroundColor);
  updateModelAndAxis();
}

void MainWindow::clear() {
  XRotation = 0;
  YRotation = 0;
  ZRotation = 0;
  XMove = 0;
  YMove = 0;
  ZMove = 0;
  scaleFactor = 1;
  sliderRotateX->setValue(XRotation);
  sliderRotateY->setValue(YRotation);
  sliderRotateZ->setValue(ZRotation);
  sliderMoveX->setValue(XMove);
  sliderMoveY->setValue(YMove);
  sliderMoveZ->setValue(ZMove);
  sliderScale->setValue(0);
  modelView->setProjectionMode(false);
  projectionMode = false;
  buttonParallelProjection->setChecked(true);

  edgesType = 0;
  edgesColor = QColor(255, 255, 255);
  edgesThickness = 1.0f;
  verticesType = 0;
  verticesColor = QColor(255, 255, 255);
  verticesThickness = 0.0f;
  backgroundColor = QColor(0, 0, 0);

  modelView->setEdgesType(edgesType);
  modelView->setLineWidth(edgesThickness);
  modelView->setPointSize(verticesThickness);
  modelView->setVerticesType(verticesType);
  modelView->setBackgroundColor(backgroundColor);
  changeEdgesColor(edgesColor);
  changeVerticesColor(verticesColor);

  updateModelAndAxis();
  ui->centralwidget->update();
}

void MainWindow::openFile() {
  setlocale(LC_NUMERIC, "C");
  QString filter = "Obj files (*.obj*)";
  QString fileName = QFileDialog::getOpenFileName(
      this, "Chose a file:", QDir::currentPath(), filter);
  QFileInfo f = fileName;
  if (fileName.isEmpty())
    qDebug() << "No file chosen";
  else {
    if (modelVerticesOrigin) {
      delete[] modelVerticesOrigin;
      delete[] modelVertices;
      delete[] modelIndices;
      delete[] modelEdgesColors;
    }
    if (modelVerticesColors) {
      delete[] modelVerticesColors;
    }
    filename = f.fileName();
    QByteArray arr = fileName.toLocal8Bit();
    char *str = arr.data();
    qDebug() << "Opened the file" << fileName << str;
    obj_info objData = (obj_info){0, 0, 0, {NULL, 0, 0}, NULL};

    parse_obj_file(str, &objData);

    modelIndicesCount = objData.count_of_indices;
    modelVerticesCount = objData.count_of_vertices * 3;
    modelVerticesOrigin = new float[modelVerticesCount];

    for (unsigned int i = 0; i < objData.matrix_3d.rows; i++) {
      for (unsigned int y = 0; y < objData.matrix_3d.columns; y++) {
        modelVerticesOrigin[i * objData.matrix_3d.columns + y] =
            objData.matrix_3d.matrix[i][y];
      }
    }

    modelIndices = new unsigned int[modelIndicesCount];
    int f_counter = 0;
    for (int i = 0; i < objData.count_of_facets; i++) {
      for (unsigned int y = 0;
           y < objData.polygons[i].number_of_vertices_in_facets * 2; y++) {
        modelIndices[f_counter] = objData.polygons[i].vertices[y];
        f_counter++;
      }
    }
    remove_obj_info(&objData);
    modelEdgesColors = new float[modelVerticesCount];
    for (int i = 0; i < modelVerticesCount; i++) {
      modelEdgesColors[i] = 1;
    }
    modelVerticesColors = new float[modelVerticesCount];
    for (int i = 0; i < modelVerticesCount; i++) {
      modelVerticesColors[i] = 1;
    }
    modelVertices = new float[modelVerticesCount];
    normalizeModel();

    copyVertexArray(modelVerticesOrigin, modelVertices, modelVerticesCount);
    modelView->setFigureData(modelVertices, modelIndices, modelEdgesColors,
                             modelVerticesColors, modelIndicesCount);
    setInfo();
    changeEdgesColor(edgesColor);
    changeVerticesColor(verticesColor);
    updateModelAndAxis();
  }
}
