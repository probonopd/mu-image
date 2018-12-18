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

void Selection::click(QPoint pos)
{
    if (state == State::inactive) {
        state = State::creating;
        scaled_origin = pos;
        origin = scaled_origin / scale_factor;

        scaled_geometry = QRect(pos, pos).normalized();
        geometry = QRect(origin, origin).normalized();

        rubberband.show();
        rubberband.setGeometry(scaled_geometry);
        emit selection_created(geometry);
    } else if (state == State::defined) {
        if (rubberband.geometry().contains(pos)) {
            state = State::moving;
            scaled_move_offset = pos - scaled_geometry.topLeft();
            move_offset = (pos / scale_factor) - geometry.topLeft();
        } else {
            state = State::creating;

            scaled_origin = pos;
            origin = scaled_origin / scale_factor;

            scaled_geometry = QRect(scaled_origin, scaled_origin);
            geometry = get_scaled_rect(scaled_geometry, 1 / scale_factor);

            rubberband.setGeometry(scaled_geometry);
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
        scaled_geometry = QRect(scaled_origin, pos).normalized();
        geometry = QRect(origin, pos / scale_factor).normalized();

        rubberband.setGeometry(scaled_geometry);
    } else if (state == State::moving) {
        scaled_geometry.setTopLeft(pos - scaled_move_offset);
        geometry.setTopLeft(pos / scale_factor - move_offset);

        rubberband.setGeometry(scaled_geometry);
    }

    emit selection_changed(geometry);

}

void Selection::mouse_released()
{
    if (state == State::creating) {
        state = State::defined;
    } else if (state == State::moving) {
        state = State::defined;
    }
}

void Selection::move_x(int x)
{
    geometry.translate(x - geometry.x(), 0);
    scaled_geometry = get_scaled_rect(geometry, scale_factor);

    auto s_signal = blockSignals(true);
    rubberband.setGeometry(scaled_geometry);
    blockSignals(s_signal);
}

void Selection::move_y(int y)
{
    geometry.translate(0, y - geometry.y());
    scaled_geometry = get_scaled_rect(geometry, scale_factor);

    auto s_signal = blockSignals(true);
    rubberband.setGeometry(scaled_geometry);
    blockSignals(s_signal);
}

void Selection::resize_width(int width)
{
    geometry.setWidth(width);
    scaled_geometry = get_scaled_rect(geometry, scale_factor);

    auto s_signal = blockSignals(true);
    rubberband.setGeometry(scaled_geometry);
    blockSignals(s_signal);
}

void Selection::resize_height(int height)
{
    geometry.setHeight(height);
    scaled_geometry = get_scaled_rect(geometry, scale_factor);

    auto s_signal = blockSignals(true);
    rubberband.setGeometry(scaled_geometry);
    blockSignals(s_signal);
}

void Selection::set_scale(double factor)
{
    scale_factor = factor;
    if (state != State::inactive) {
        scaled_origin = origin * factor;
        scaled_geometry = get_scaled_rect(geometry, factor);
        rubberband.setGeometry(scaled_geometry);
    }
}

/**
 * since we can multiple QPoints by floats,
 * but not QRects
 */
QRect Selection::get_scaled_rect(QRect rect, double scale) const
{
    {
        auto point = rect.topLeft();
        point *= scale;
        rect.setTopLeft(point);
    }
    {
        auto point = rect.bottomRight();
        point *= scale;
        rect.setBottomRight(point);
    }
    return rect;
}
