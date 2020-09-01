#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "SamplesConfig.h"
#include "soundsampletablemodel.h"
#include "wavfile.h"

#include <QtCore/qglobal.h>
#if QT_VERSION >= 0x050000
#include <QtWidgets/QMainWindow>

#include <QAudioOutput>
#include <QDebug>
#include <QFile>

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
  SoundSampleTableModel *model, *selectedSamplesModel;
  int selectedSampleId;
  QAudioOutput *audioOutput;
  WavFile audioFile;
  // QWidget interface
protected:
  virtual void keyPressEvent(QKeyEvent *event) override;
private slots:
  void on_btnTestSample_clicked();
  void onSampleRowActivated(const QModelIndex &index, const QModelIndex &prev);
  void on_btnAddSample_clicked();
  void on_pushButton_clicked();
  void on_pushButton_2_clicked();

  void playAudio(QString p);
  void handleStateChanged(QAudio::State state);
  void on_actionAbout_Qt_triggered();
  void on_actionAbout_triggered();
};
#endif // MAINWINDOW_H
