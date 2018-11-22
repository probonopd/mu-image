#include "mainwindow.h"
#include "image.h"
#include "../ui/ui_mainwindow.h"

#include <QtWidgets>
#include <QFileDialog>
#include <QDebug>
#include <QSize>

#include <QMessageBox>
#include <QGuiApplication>

#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    image{}
{
	ui->setupUi(this);

    createActions();
    disable_action_buttons();

    hide_panels();

    setCentralWidget(&image);
    resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
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
	ui->actionZoomIn->setShortcut(QKeySequence::ZoomIn);
	ui->actionZoomDefault->setShortcut(Qt::CTRL + Qt::Key_1);
	ui->actionZoomOut->setShortcut(QKeySequence::ZoomOut);
	ui->actionQuit->setShortcut(QKeySequence::Quit);
}

void MainWindow::do_load()
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
        // setWindowFilePath(filename);
        enable_action_buttons();

    } else {
        disable_action_buttons();
        show_error_message(image.get_error_message());
    }
    hide_panels();
}

void MainWindow::do_save()
{
    // no dialog, just save the file
}

void MainWindow::do_resize()
{
    qDebug() << "resize";
    active_action = Action::resize;
    ui->stackedPanels->setCurrentIndex(1);
}

void MainWindow::do_crop()
{
    qDebug() << "crop";
    active_action = Action::crop;
    ui->stackedPanels->setCurrentIndex(2);
}

void MainWindow::do_transparency()
{
    qDebug() << "transparency";
    active_action = Action::transparency;
}

void MainWindow::apply_resize()
{
    qDebug() << "resize apply";
    ui->stackedPanels->setCurrentIndex(0);
    active_action = Action::none;
}

void MainWindow::apply_crop()
{
    qDebug() << "crop apply";
    ui->stackedPanels->setCurrentIndex(0);
    selection.stop();
    active_action = Action::none;
}

void MainWindow::apply_transparency()
{
    qDebug() << "transparency apply";
    ui->stackedPanels->setCurrentIndex(0);
    active_action = Action::none;
}

void MainWindow::do_zoom_in()
{
    qDebug() << "zoom in";
}

void MainWindow::do_zoom_default()
{
    qDebug() << "default zoom";
}

void MainWindow::do_zoom_out()
{
    qDebug() << "zoom out";
}

void MainWindow::do_help()
{
    // probably, put the help in the side pane
}

void MainWindow::do_close()
{
    disable_action_buttons();
}

void MainWindow::show_error_message(QString message)
{
    QMessageBox::information(this, QGuiApplication::applicationDisplayName(), message);
}

void MainWindow::hide_panels()
{
    ui->stackedPanels->setCurrentIndex(0);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (active_action == Action::crop && image.underMouse()) {
        selection.start(event->pos());
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (selection.is_active()) {
        selection.mouse_moved(event->pos());
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    selection.mouse_released();
}

void MainWindow::enable_action_buttons()
{
    ui->actionSave->setEnabled(true);
    ui->actionResize->setEnabled(true);
    ui->actionCrop->setEnabled(true);
    ui->actionTransparency->setEnabled(true);
    ui->actionZoomIn->setEnabled(true);
    ui->actionZoomDefault->setEnabled(true);
    ui->actionZoomOut->setEnabled(true);
}

void MainWindow::disable_action_buttons()
{
    ui->actionSave->setEnabled(false);
    ui->actionResize->setEnabled(false);
    ui->actionCrop->setEnabled(false);
    ui->actionTransparency->setEnabled(false);
    ui->actionZoomIn->setEnabled(false);
    ui->actionZoomDefault->setEnabled(false);
    ui->actionZoomOut->setEnabled(false);
}
/*
void MainWindow::about()
{
    QMessageBox::about(this, tr("About this sample"),
        tr("This <i>Sample</i> creates a window with a menu bar."));
}
*/
