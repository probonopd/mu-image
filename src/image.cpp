#include "image.h"

#include <QDebug>

#include <QLabel>


#include <QMainWindow>
#include <QDir>
#include <QStatusBar>

#include <QString>
#include <QImageReader>
#include <QImage>
#include <QPaintEvent>
#include <QPainter>
#include <QRect>
#include <QPoint>

#include "mainwindow.h"

Image::Image(MainWindow* parent):
    parent{parent},
    selection{this},
    QLabel()
{
    setBackgroundRole(QPalette::Base);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    setScaledContents(true);

    initUndo();

}

Image::~Image()
{
}

void Image::initUndo() {
}

bool Image::open(QString filename)
{
    this->filename = filename;

    QImageReader reader(filename);
    reader.setAutoTransform(true);
    image = reader.read();
    if (image.isNull()) {
        error_message = tr("Cannot load %1: %2")
            .arg(QDir::toNativeSeparators(filename), reader.errorString());
        return false;
    }

    update_view();

    setWindowFilePath(filename);

    status_message = tr("Opened \"%1\", %2x%3")
        .arg(QDir::toNativeSeparators(filename)).arg(image.width()).arg(image.height());
    return true;

}

void Image::update_view()
{
    setPixmap(QPixmap::fromImage(image));
    scale_factor = 1.0;

    setVisible(true);

    adjustSize();
}

void Image::crop()
{
    image = image.copy(selection.shape());
    update_view();
}

void Image::scale(double factor)
{

    if (factor == 1.0) {
        scale_factor = 1.0;
    } else {
        scale_factor *= factor;
    }

    selection.set_scale(scale_factor);

    resize(scale_factor * pixmap()->size());

}

void Image::mousePressEvent(QMouseEvent *event)
{
    if (can_select) {
        selection.click(event->pos());
    }
}

void Image::mouseReleaseEvent(QMouseEvent *event)
{
    if (selection.is_active()) {
        selection.mouse_released();
    }
}


void Image::mouseMoveEvent(QMouseEvent *event)
{
    if (selection.is_active()) {
        selection.mouse_moved(event->pos());
    }
}

void Image::create_selection(QRect geometry)
{
    emit selection_changed(geometry);
}

void Image::change_selection(QRect geometry)
{
    selection_shape = geometry;
    emit selection_changed(geometry);
}

void Image::change_selection_x(int x)
{
    selection.move_x(x);
}

void Image::change_selection_y(int y)
{
    selection.move_y(y);
}

void Image::change_selection_width(int width)
{
    selection.resize_width(width);
}
void Image::change_selection_height(int height)
{
    selection.resize_height(height);
}


void Image::enable_selection(bool enable)
{
    can_select = enable;

    if (enable == true) {
        selection_connection = connect(
            &selection, &Selection::selection_changed,
            this, &Image::change_selection
        );
    } else {
        QObject::disconnect(selection_connection);
    }
}

void Image::stop_selection()
{
    selection.stop();
}

void Image::contextMenuEvent(QContextMenuEvent *event)
{
    parent->contextMenu.popup(event->globalPos());
}
