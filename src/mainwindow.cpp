#include "mainwindow.h"
#include "image.h"
#include "../ui/ui_mainwindow.h"

#include <QtWidgets>
#include <QFileDialog>
#include <QDebug>
#include <QSize>

#include <QMessageBox>
#include <QGuiApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    image{}
{
	ui->setupUi(this);
    createActions();

    ui->stackedPanels->setCurrentIndex(0);

    setCentralWidget(&image);
    const auto size{QGuiApplication::primaryScreen()->availableSize() * 3 / 5};
    resize(size);
    // resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
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
    if (filenames.size() != 1) {
        return;
    }

    filename = filenames.at(0);

    if (image.open(filename)) {
        statusBar()->showMessage(image.get_status_message());
        enable_action_buttons();
    } else {
        show_error_message(image.get_error_message());
    }
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
    // probably, put the help in the side pane
}

void MainWindow::close()
{
    disable_action_buttons();
}

void MainWindow::show_error_message(QString message)
{
    QMessageBox::information(this, QGuiApplication::applicationDisplayName(), message);
}

void MainWindow::enable_action_buttons()
{
}

void MainWindow::disable_action_buttons()
{
}
/*
void MainWindow::about()
{
    QMessageBox::about(this, tr("About this sample"),
        tr("This <i>Sample</i> creates a window with a menu bar."));
}
*/
