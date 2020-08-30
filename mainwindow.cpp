#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "samplemanager.h"

#include "samplessummarytablemodel.h"
#include "soundsampletablemodel.h"
#include <QDebug>
#include <QKeyEvent>
#include <QSound>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  model = new SoundSampleTableModel;
  selectedSamplesModel = new SoundSampleTableModel(false);
  //  ui->samplesTable->setModel(new SamplesSummaryTableModel());
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
  //  auto selected = ui->samplesTable->selectedIndexes().first();
  auto sample = SampleManager::getInstance()->getById(selectedSampleId);
  QSound::play(sample->getFullPath());
}

void MainWindow::onSampleRowActivated(const QModelIndex &index,
                                      const QModelIndex &prev) {

  auto sampleId = index.siblingAtColumn(0).data();
  selectedSampleId = sampleId.value<int>();
  qInfo() << "sample id selected: " << selectedSampleId;
}

void MainWindow::on_btnAddSample_clicked() {
  auto sample = SampleManager::getInstance()->getById(selectedSampleId);
  selectedSamplesModel->addSample(sample);
}

void MainWindow::on_pushButton_clicked() {
  for (auto s : selectedSamplesModel->getSamples()) {
    QSound::play(s->getFullPath());
  }
}

void MainWindow::on_pushButton_2_clicked() {
  selectedSamplesModel->setSamples({});
}
