#ifndef IMAGE_H
#define IMAGE_H

#include "selection.h"

#include <QLabel>

class QMainWindow;
class QImage;

class Image : public QLabel
{
    Q_OBJECT

    public:
        explicit Image();
        ~Image();
        bool open(QString filename);
        // void paintEvent(QPaintEvent *event) override;
        QString get_status_message() { return status_message; }
        QString get_error_message() { return error_message; }

        int view_width() { return width(); }
        int view_height() { return width(); }
        void crop();
        void scale(double factor);
        double get_scale() { return scale_factor; }
        void enable_selection(bool enable = true);
        void stop_selection();
        // TODO: not a good idea... how to proxy the signal?
        Selection& get_selection() { return selection; }

        void mousePressEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;
    public slots:
        void create_selection(QRect geometry);
        void change_selection(QRect geometry);
        void change_selection_x(int x);
        void change_selection_y(int y);
        void change_selection_width(int width);
        void change_selection_height(int height);
    signals:
        void selection_changed(QRect geometry);
    private:
		void update_view();

        QImage image;
        QString filename;

        double scale_factor{1.0};

        QString status_message{};
        QString error_message{};

        Selection selection;
        bool can_select{false};
        QRect selection_shape{};
        QMetaObject::Connection selection_connection;
};

#endif
