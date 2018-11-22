#ifndef IMAGE_H
#define IMAGE_H

#include <QScrollArea>

class QMainWindow;
class QLabel;
class QImage;

class Image : public QScrollArea
{
    public:
        explicit Image();
        ~Image();
        bool open(QString filename);
        void update_view();
        void paintEvent(QPaintEvent *event) override;
        QString get_status_message() { return status_message; }
        QString get_error_message() { return error_message; }

        bool underMouse();
    private:
		void set_image(const QImage &image_new);

        QImage image;
        QString filename;

        QScrollArea *image_scroll_area;
        QLabel *image_label;
        double scale_factor{1.0};

        QString status_message{};
        QString error_message{};
};

#endif
