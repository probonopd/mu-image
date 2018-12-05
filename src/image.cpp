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

Image::Image():
    selection{this},
    QLabel()
{
    setBackgroundRole(QPalette::Base);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    setScaledContents(true);
}

Image::~Image()
{
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

    /*
void Image::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirty_rect = event->rect();
    painter.drawImage(dirty_rect, image_view, dirty_rect);
    qDebug() << "...";
}
    */

void Image::crop()
{
    image = image.copy(selection.shape());
    update_view();
}

void Image::scale(double factor)
{
    selection.scale(1.25);

    if (factor == 1.0) {
        scale_factor = 1.0;
    } else {
        scale_factor *= factor;
    }

    resize(scale_factor * pixmap()->size());

}

void Image::mousePressEvent(QMouseEvent *event)
{
    if (can_select) {
        start_selection(event->pos());
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

void Image::start_selection(QPoint pos)
{
    selection.start(pos);
}

void Image::stop_selection()
{
    selection.stop();
}
