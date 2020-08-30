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
  //  ui->samplesTable->setModel(new SamplesSummaryTableModel());
  ui->samplesTable->setModel(model);
  ui->samplesTable->resizeColumnsToContents();

  connect(ui->filterInput, &QLineEdit::textChanged, model,
          &SoundSampleTableModel::filterSamples);

  connect(ui->samplesTable, &QTableView::pressed, this,
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

void MainWindow::onSampleRowActivated(const QModelIndex &index) {
  //  auto model = ui->samplesTable->model();
  auto sampleId = index.siblingAtColumn(0).data();
  selectedSampleId = sampleId.value<int>();
  qInfo() << "sample id selected: " << selectedSampleId;
}
