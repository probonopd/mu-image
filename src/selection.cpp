#include "selection.h"

#include <QDebug>

Selection::Selection(QMainWindow *parent) :
    rubberband{QRubberBand::Rectangle, parent}
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
        // qDebug() << rubberband.geometry().contains(pos);
        // qDebug() << rubberband.underMouse();
        if (rubberband.geometry().contains(pos)) {
            state = State::moving;
            move_offset = pos - rubberband.pos();
        } else {
            stop();
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
    }
    emit selection_changed(rubberband.geometry());
}

void Selection::mouse_released()
{
    if (state == State::creating) {
        state = State::defined;
    } else if (state == State::moving) {
        state = State::defined;
    }
}

void Selection::change_selection(QRect geometry)
{
}
