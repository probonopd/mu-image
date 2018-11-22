#include "image.h"

#include <QDebug>

#include <QScrollArea>
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

Image::Image():
    image_label(new QLabel)
{
    image_label->setBackgroundRole(QPalette::Base);
    image_label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    image_label->setScaledContents(false);

    setBackgroundRole(QPalette::Dark);
    setWidget(image_label);
    setVisible(false);
}

Image::~Image()
{
    delete image_label;
}

bool Image::open(QString filename)
{
    this->filename = filename;

    QImageReader reader(filename);
    reader.setAutoTransform(true);
    const QImage image_new = reader.read();
    if (image_new.isNull()) {
        error_message = tr("Cannot load %1: %2")
            .arg(QDir::toNativeSeparators(filename), reader.errorString());
        return false;
    }

    set_image(image_new);

    setWindowFilePath(filename);

    status_message = tr("Opened \"%1\", %2x%3")
        .arg(QDir::toNativeSeparators(filename)).arg(image_new.width()).arg(image_new.height());
    return true;

}

void Image::set_image(const QImage &image_new)
{
    image = image_new;
    image_label->setPixmap(QPixmap::fromImage(image));
    scale_factor = 1.0;

    setVisible(true);

    image_label->adjustSize();
}

void Image::update_view()
{
    // TODO: scale to something sensible (photoTweaker is scaling to the window size... we should not do the same.)
    /*
    image_view = image_original;
    update();
    */
}

void Image::paintEvent(QPaintEvent *event)
{
    /*
    QPainter painter(this);
    QRect dirty_rect = event->rect();
    painter.drawImage(dirty_rect, image_view, dirty_rect);
    qDebug() << "...";
    */
}

bool Image::underMouse()
{
    return image_label->underMouse();
}
