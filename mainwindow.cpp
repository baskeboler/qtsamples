#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "samplemanager.h"

#include "SamplesConfig.h"
#include "samplessummarytablemodel.h"
#include "soundsampletablemodel.h"
#include <QDebug>
#include <QKeyEvent>
#include <QMessageBox>
#include <QSound>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  model = new SoundSampleTableModel;
  selectedSamplesModel = new SoundSampleTableModel(false);
  ui->samplesTable->setModel(model);
  ui->selectedSamplesTable->setModel(selectedSamplesModel);
  ui->samplesTable->resizeColumnsToContents();
  ui->selectedSamplesTable->resizeColumnsToContents();
  connect(ui->filterInput, &QLineEdit::textChanged, model,
          &SoundSampleTableModel::filterSamples);

  connect(ui->samplesTable->selectionModel(),
          &QItemSelectionModel::currentRowChanged, this,
          &MainWindow::onSampleRowActivated);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key::Key_Escape) {
    QApplication::quit();
  }
}

void MainWindow::on_btnTestSample_clicked() {
  auto sample = SampleManager::getInstance()->getById(selectedSampleId);
  playAudio(sample->getFullPath());
}

void MainWindow::onSampleRowActivated(const QModelIndex &index,
                                      const QModelIndex &prev) {

  auto sampleId = index.siblingAtColumn(0).data();
  selectedSampleId = sampleId.value<int>();
  qInfo() << "sample id selected: " << selectedSampleId;
}

void MainWindow::on_btnAddSample_clicked() {
  auto selected = ui->samplesTable->selectionModel()->selectedRows();
  for (auto s : selected) {
    int sampleId = s.siblingAtColumn(0).data().toInt();
    auto sample = SampleManager::getInstance()->getById(sampleId);
    selectedSamplesModel->addSample(sample);
  }
}

void MainWindow::on_pushButton_clicked() {
  for (const auto &s : selectedSamplesModel->getSamples()) {
    QSound::play(s->getFullPath());
  }
}

void MainWindow::on_pushButton_2_clicked() {
  selectedSamplesModel->setSamples({});
}

#ifndef USE_SIMPLE_AUDIO_PLAYBACK
void MainWindow::playAudio(QString p) {
  QAudioDeviceInfo deviceInfo{QAudioDeviceInfo::defaultOutputDevice()};
  audioFile.open(p);
  QAudioFormat format{audioFile.fileFormat()};
  // Set up the format, eg.

  format.setSampleRate(44100);
  format.setChannelCount(1);
  format.setSampleSize(32);
  format.setCodec("audio/pcm");
  //  format.setByteOrder(QAudioFormat::LittleEndian);
  format.setSampleType(QAudioFormat::Float);
  if (!deviceInfo.isFormatSupported(format)) {
    qWarning()
        << "Raw audio format not supported by backend, cannot play audio.";
    return;
  }
  //  audioFile.reset();
  //  audioFile.open(QIODevice::ReadOnly);
  //  audioFile.seek(0);

  audioOutput = new QAudioOutput{deviceInfo, format, this};
  audioOutput->setNotifyInterval(100);
  // audioOutput->
  connect(audioOutput, &QAudioOutput::stateChanged, this,
          &MainWindow::handleStateChanged);
  audioOutput->start(&audioFile);
  //  QAudio::convertVolume(audioOutput->volume(), )
  //  audioOutput->setVolume(1.0);
  //  f->deleteLater();
}

#else
void MainWindow::playAudio(QString p) { QSound::play(p); }
#endif

void MainWindow::handleStateChanged(QAudio::State newState) {
  qInfo() << "state changed: " << newState;
  switch (newState) {
  case QAudio::IdleState:
    // Finished playing (no more data)
    audioOutput->stop();
    audioFile.close();
    delete audioOutput;
    break;

  case QAudio::StoppedState:
    // Stopped for other reasons
    if (audioOutput->error() != QAudio::NoError) {
      // Error handling
      qWarning() << "there was an error";
    }
    break;

  default:
    // ... other cases as appropriate
    break;
  }
}

void MainWindow::on_actionAbout_Qt_triggered() { QApplication::aboutQt(); }

void MainWindow::on_actionAbout_triggered() {
  QString appName = QString("%1 v%2.%3")
                        .arg("qtsamples")
                        .arg(qtsamples_VERSION_MAJOR)
                        .arg(qtsamples_VERSION_MINOR);
  QString desc = QString("%1: a toy audio samples application").arg(appName);
  QMessageBox::about(this, appName, desc);
}
