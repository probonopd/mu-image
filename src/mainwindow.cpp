#include "mainwindow.h"
#include "../ui/ui_mainwindow.h"

#include <QtWidgets>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);
    createActions();

    ui->stackedPanels->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions()
{
	ui->actionLoad->setShortcut(QKeySequence::Open);
	ui->actionSave->setShortcut(QKeySequence::Save);
	ui->actionSave->setShortcut(QKeySequence::HelpContents);
	// ui->actionZoomIn->setShortcut(QKeySequence::ZoomIn);
	// ui->actionZoomOut->setShortcut(QKeySequence::ZoomOut);
	ui->actionQuit->setShortcut(QKeySequence::Quit);
}

void MainWindow::load()
{

    // getting the latest path from the settings:
    // https://stackoverflow.com/questions/3597900/qsettings-file-chooser-should-remember-the-last-directory
    // https://stackoverflow.com/questions/50347610/qt-file-dialog-doesnt-remember-the-last-directory-after-restarting-project

    // auto fileName = QFileDialog::getOpenFileName(this,
        // tr("Open Image"), "/home/jana", tr("Image Files (*.png *.jpg)"));
    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
	QStringList mimeTypeFilters;
	mimeTypeFilters
		// << "image/jpeg"
		<< "image/png";
	dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.exec();
    auto filenames = dialog.selectedFiles();
    QString filename{};
    if (filenames.size() == 1) {
        filename = filenames.at(0);
    }
    qDebug() << filename;
}

void MainWindow::save()
{
    // no dialog, just save the file
}

void MainWindow::resize()
{
    qDebug() << "resize";
    ui->stackedPanels->setCurrentIndex(1);
}

void MainWindow::crop()
{
    qDebug() << "crop";
    ui->stackedPanels->setCurrentIndex(2);
}

void MainWindow::transparency()
{
    qDebug() << "transparency";
}

void MainWindow::resize_apply()
{
    qDebug() << "resize apply";
    ui->stackedPanels->setCurrentIndex(0);
}

void MainWindow::crop_apply()
{
    qDebug() << "crop apply";
    ui->stackedPanels->setCurrentIndex(0);
}

void MainWindow::transparency_apply()
{
    qDebug() << "transparency apply";
    ui->stackedPanels->setCurrentIndex(0);
}

void MainWindow::help()
{
}
/*
void MainWindow::about()
{
    QMessageBox::about(this, tr("About this sample"),
        tr("This <i>Sample</i> creates a window with a menu bar."));
}
*/
