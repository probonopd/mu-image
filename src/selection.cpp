#include "selection.h"

#include <QDebug>

Selection::Selection(QWidget *parent) :
    Selection(parent, {0, 0})
{
}

Selection::Selection(QWidget *parent, QPoint origin) :
    rubberband{QRubberBand::Rectangle, parent},
    parent_origin{origin}
{
}

void Selection::start(QPoint pos)
{
    if (state == State::inactive) {
        state = State::creating;
        origin = pos;
        rubberband.show();
        rubberband.setGeometry(QRect(pos, pos).normalized());
    } else if (state == State::defined) {
        if (rubberband.geometry().contains(pos)) {
            state = State::moving;
            move_offset = pos - rubberband.pos();
        } else {
            state = State::creating;
            origin = pos;
            rubberband.setGeometry(QRect(pos, pos).normalized());
        }
    }
}

void Selection::stop()
{
    state = State::inactive;
    rubberband.hide();
    rubberband.move(0, 0);
}

void Selection::mouse_moved(QPoint pos)
{
    if (state == State::creating) {
        rubberband.setGeometry(QRect(origin, pos).normalized());
    } else if (state == State::moving) {
        rubberband.move(pos - move_offset);
        qDebug() << rubberband.y();
    }
    auto image_geometry{rubberband.geometry()};
    image_geometry.setX(image_geometry.x() - parent_origin.x());
    image_geometry.setY(image_geometry.y() - parent_origin.y());
    // image_geometry.moveTopLeft(parent_origin);
    emit selection_changed(image_geometry);
}

void Selection::mouse_released()
{
    if (state == State::creating) {
        state = State::defined;
    } else if (state == State::moving) {
        state = State::defined;
    }
}

void Selection::scale(double factor)
{
    if (factor == 1.0) {
        scale_rubberband(1.0 / scale_factor);
        scale_factor = 1.0;
    } else {
        scale_factor *= factor;
        scale_rubberband(factor);
    }

}

void Selection::scale_rubberband(double factor)
{
    if (state != State::inactive) {
        origin = parent_origin + (origin - parent_origin) * factor;
        QPoint end{origin.x() + (int) (rubberband.width() * factor), origin.y() + (int) (rubberband.height() * factor)};
        rubberband.setGeometry(QRect(origin, end).normalized());
    }
}

void Selection::change_selection_x(int x)
{
    rubberband.move(x, rubberband.y());
}
void Selection::change_selection_y(int y)
{
    rubberband.move(rubberband.x(), y);
}
void Selection::change_selection_width(int width)
{
    rubberband.resize(width, rubberband.height());
}
void Selection::change_selection_height(int height)
{
    rubberband.resize(rubberband.width(), height);
}
