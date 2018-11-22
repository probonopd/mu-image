#ifndef SELECTION_H
#define SELECTION_H

#include <QRubberBand>
#include <QMainWindow>

class Selection : public QRubberBand
{
    Q_OBJECT

    enum class State
    {
        inactive, creating, moving, defined
    };

    public:
        explicit Selection(QMainWindow *parent);

        bool is_active() { return state != State::inactive; }

        void start(QPoint pos);
        void stop();
        void mouse_moved(QPoint pos);
        void mouse_released();
    private:
        State state{State::inactive};
};

#endif
