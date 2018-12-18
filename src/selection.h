#ifndef SELECTION_H
#define SELECTION_H

#include <QMainWindow>
#include <QRubberBand>
#include <QRect>
#include <QPoint>

class Selection : public QObject
{
    Q_OBJECT

    enum class State
    {
        inactive, creating, moving, defined
    };

    public:
        explicit Selection(QWidget *parent);
        explicit Selection(QWidget *parent, QPoint origin);

        bool is_active() const { return state != State::inactive; }

        void click(QPoint pos);
        void stop();
        void mouse_moved(QPoint pos);
        void mouse_released();
        void move_x(int x);
        void move_y(int y);
        void resize_width(int width);
        void resize_height(int height);
        QRect shape() const { return geometry; }
        void set_shape(QRect shape) {  rubberband.setGeometry(shape.normalized()); }
        void set_scale(double factor);
    signals:
        void selection_created(QRect geometry);
        void selection_changed(QRect geometry);
    private:
        // TODO: to be deleted...
        QPoint parent_origin{};
        QRubberBand rubberband;
        QRect geometry{};
        QRect scaled_geometry{};
        State state{State::inactive};
        QPoint origin{};
        QPoint scaled_origin{};
        double scale_factor{1.0};
        QPoint scaled_move_offset{};
        QPoint move_offset{};

        QRect get_scaled_rect(QRect rect, double scale) const;
};

#endif
