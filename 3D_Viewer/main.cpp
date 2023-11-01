#include <QApplication>
#include <QDesktopWidget>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;

  QDesktopWidget *desktop = QApplication::desktop();
  int screenWidth = desktop->width();
  int screenHeight = desktop->height();
  // Получаем размер окна
  int windowWidth = w.width();
  int windowHeight = w.height();
  // Вычисляем координаты для центрирования окна
  int x = (screenWidth - windowWidth) / 3;
  int y = (screenHeight - windowHeight) / 3;
  w.move(x, y);

  w.show();
  return a.exec();
}
