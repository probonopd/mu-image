#include "mainwindow.h"
#include "image.h"
#include "../ui/ui_mainwindow.h"

#include <QtWidgets>
#include <QFileDialog>
#include <QDebug>
#include <QRect>

#include <QMessageBox>
#include <QGuiApplication>

#include <QScrollBar>

#include <QMouseEvent>
#include <QSpinBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    image{}
{
	ui->setupUi(this);

    createActions();
    disable_action_buttons();

    hide_panels();

    scroll_area.setBackgroundRole(QPalette::Dark);
    scroll_area.setWidget(&image);
    scroll_area.setVisible(true);

    connect(ui->stackedPanels, &QStackedWidget::currentChanged, this, &MainWindow::on_panel_focus);

    setCentralWidget(&scroll_area);
    resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
    // qDebug() << image.geometry().topLeft();
    // qDebug() << image.pos();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_panel_focus(int i)
{
    if (active_action == Action::crop) {
        close_crop();
    }
}

void MainWindow::createActions()
{
	ui->actionLoad->setShortcut(QKeySequence::Open);
	ui->actionSave->setShortcut(QKeySequence::Save);
	ui->actionSave->setShortcut(QKeySequence::HelpContents);
	ui->actionResize->setShortcut(Qt::CTRL + Qt::Key_R);
	ui->actionCrop->setShortcut(Qt::CTRL + Qt::Key_C);
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
    ui->stackedPanels->setCurrentIndex(1);
    active_action = Action::resize;
}

void MainWindow::do_crop()
{

    ui->stackedPanels->setCurrentIndex(2);


    active_action = Action::crop;

    ui->cropXSpinBox->setMaximum(image.width());
    ui->cropYSpinBox->setMaximum(image.height());
    ui->cropWidthSpinBox->setMaximum(image.width());
    ui->cropHeightSpinBox->setMaximum(image.height());


    image.enable_selection();

    crop_connection.append(connect(
        &image, &Image::selection_changed,
        this, &MainWindow::change_crop_selection
    ));

    crop_connection.append(connect(
        ui->cropXSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
        &image, &Image::change_selection_x
    ));
    crop_connection.append(connect(
        ui->cropYSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
        &image, &Image::change_selection_y
    ));
    crop_connection.append(connect(
        ui->cropWidthSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
        &image, &Image::change_selection_width
    ));
    crop_connection.append(connect(
        ui->cropHeightSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
        &image, &Image::change_selection_height
    ));
}

void MainWindow::change_crop_selection(QRect geometry)
{
    auto x_signal = ui->cropXSpinBox->blockSignals(true);
    auto y_signal = ui->cropYSpinBox->blockSignals(true);
    auto w_signal = ui->cropWidthSpinBox->blockSignals(true);
    auto h_signal = ui->cropHeightSpinBox->blockSignals(true);

    ui->cropXSpinBox->setValue(geometry.x());
    ui->cropWidthSpinBox->setValue(geometry.width());
    ui->cropYSpinBox->setValue(geometry.y());
    ui->cropHeightSpinBox->setValue(geometry.height());

    ui->cropXSpinBox->blockSignals(x_signal);
    ui->cropYSpinBox->blockSignals(y_signal);
    ui->cropWidthSpinBox->blockSignals(w_signal);
    ui->cropHeightSpinBox->blockSignals(h_signal);
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
    image.crop();
    close_crop();
}

void MainWindow::apply_transparency()
{
    qDebug() << "transparency apply";
    ui->stackedPanels->setCurrentIndex(0);
    active_action = Action::none;
}

void MainWindow::close_crop()
{
    for (auto& connection: crop_connection) {
        QObject::disconnect(connection);
    }
    ui->stackedPanels->setCurrentIndex(0);
    ui->cropXSpinBox->setValue(0);
    ui->cropYSpinBox->setValue(0);
    ui->cropWidthSpinBox->setValue(0);
    ui->cropHeightSpinBox->setValue(0);
    active_action = Action::none;
    image.stop_selection();
    image.enable_selection(false);
}

void MainWindow::do_zoom_in()
{
    image.scale(1.25);
    scale_scroll_bar();
}

void MainWindow::do_zoom_default()
{
    image.scale(1.0);
    scale_scroll_bar();
}

void MainWindow::do_zoom_out()
{
    image.scale(0.8);
    scale_scroll_bar();
}

void MainWindow::scale_scroll_bar()
{
    auto scale_factor = image.get_scale();

    auto h = scroll_area.horizontalScrollBar();
    h->setValue(int(h->value() * scale_factor +
        ((scale_factor - 1) * h->pageStep() / 2)));
    auto v = scroll_area.horizontalScrollBar();
    v->setValue(int(v->value() * scale_factor +
        ((scale_factor - 1) * v->pageStep() / 2)));
    // scrollBar->setValue(int(factor * scrollBar->value() +
        // ((factor - 1) * scrollBar->pageStep()/2)));
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
