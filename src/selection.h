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
        explicit Selection(QMainWindow *parent);

        bool is_active() const { return state != State::inactive; }

        void start(QPoint pos);
        void stop();
        void mouse_moved(QPoint pos);
        void mouse_released();
        QRect shape() const { return rubberband.geometry(); }
    public slots:
        void change_selection(QRect geometry);
    signals:
        void selection_changed(QRect geometry);
    private:
        QRubberBand rubberband;
        State state{State::inactive};
        QPoint origin{};
        QPoint move_offset{};
};

#endif
