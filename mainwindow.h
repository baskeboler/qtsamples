#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "soundsampletablemodel.h"

#include <QtCore/qglobal.h>
#if QT_VERSION >= 0x050000
#include <QtWidgets/QMainWindow>
#else
#include <QtGui/QMainWindow>
#endif

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

private:
  Ui::MainWindow *ui;
  SoundSampleTableModel *model;
  // QWidget interface
protected:
  virtual void keyPressEvent(QKeyEvent *event) override;
};
#endif // MAINWINDOW_H
