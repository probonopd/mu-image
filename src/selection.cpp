#include "selection.h"

#include <QDebug>

Selection::Selection(QMainWindow *parent) :
    QRubberBand(QRubberBand::Rectangle, parent)
{
}

void Selection::start(QPoint pos)
{
    if (state == State::inactive) {
        state = State::creating;
        show();
        setGeometry(QRect(pos, pos).normalized());
    } else if (state == State::defined) {
        state = State::moving;
    }
}

void Selection::stop()
{
    state = State::inactive;
    hide();
}

void Selection::mouse_moved(QPoint pos)
{
    if (state == State::creating) {
        setGeometry(QRect(this->pos(), pos).normalized());
    } else if (state == State::creating) {
    }
}

void Selection::mouse_released()
{
    if (state == State::creating) {
    } else if (state == State::moving) {
    }
}
