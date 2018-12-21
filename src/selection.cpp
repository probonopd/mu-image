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
        zoomed_origin = pos;
        origin = zoomed_origin / zoom_factor;

        zoomed_geometry = QRect(pos, pos).normalized();
        geometry = QRect(origin, origin).normalized();

        rubberband.show();
        rubberband.setGeometry(zoomed_geometry);
        emit selection_created(geometry);
    } else if (state == State::defined) {
        if (rubberband.geometry().contains(pos)) {
            state = State::moving;
            zoomed_move_offset = pos - zoomed_geometry.topLeft();
            move_offset = (pos / zoom_factor) - geometry.topLeft();
        } else {
            state = State::creating;

            zoomed_origin = pos;
            origin = zoomed_origin / zoom_factor;

            zoomed_geometry = QRect(zoomed_origin, zoomed_origin);
            geometry = get_zoomed_rect(zoomed_geometry, 1 / zoom_factor);

            rubberband.setGeometry(zoomed_geometry);
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
        zoomed_geometry = QRect(zoomed_origin, pos).normalized();
        geometry = QRect(origin, pos / zoom_factor).normalized();

        rubberband.setGeometry(zoomed_geometry);
    } else if (state == State::moving) {
        zoomed_geometry.setTopLeft(pos - zoomed_move_offset);
        geometry.setTopLeft(pos / zoom_factor - move_offset);

        rubberband.setGeometry(zoomed_geometry);
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
    zoomed_geometry = get_zoomed_rect(geometry, zoom_factor);

    auto s_signal = blockSignals(true);
    rubberband.setGeometry(zoomed_geometry);
    blockSignals(s_signal);
}

void Selection::move_y(int y)
{
    geometry.translate(0, y - geometry.y());
    zoomed_geometry = get_zoomed_rect(geometry, zoom_factor);

    auto s_signal = blockSignals(true);
    rubberband.setGeometry(zoomed_geometry);
    blockSignals(s_signal);
}

void Selection::resize_width(int width)
{
    geometry.setWidth(width);
    zoomed_geometry = get_zoomed_rect(geometry, zoom_factor);

    auto s_signal = blockSignals(true);
    rubberband.setGeometry(zoomed_geometry);
    blockSignals(s_signal);
}

void Selection::resize_height(int height)
{
    geometry.setHeight(height);
    zoomed_geometry = get_zoomed_rect(geometry, zoom_factor);

    auto s_signal = blockSignals(true);
    rubberband.setGeometry(zoomed_geometry);
    blockSignals(s_signal);
}

void Selection::set_zoom(double factor)
{
    zoom_factor = factor;
    if (state != State::inactive) {
        zoomed_origin = origin * factor;
        zoomed_geometry = get_zoomed_rect(geometry, factor);
        rubberband.setGeometry(zoomed_geometry);
    }
}

/**
 * since we can multiple QPoints by floats,
 * but not QRects
 */
QRect Selection::get_zoomed_rect(QRect rect, double zoom) const
{
    {
        auto point = rect.topLeft();
        point *= zoom;
        rect.setTopLeft(point);
    }
    {
        auto point = rect.bottomRight();
        point *= zoom;
        rect.setBottomRight(point);
    }
    return rect;
}
