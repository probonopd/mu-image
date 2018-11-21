#include <QApplication>
#include <QDebug>

#include "src/muimage.h"
#include "src/mainwindow.h"

int main(int argc, char *argv[])
{
	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    MuImage app(argc, argv);

    MainWindow main_window;
    main_window.show();

    return app.exec();
}
