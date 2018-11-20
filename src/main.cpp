#include <QDebug>

#include "src/muimage.h"
#include "src/mainwindow.h"

int main(int argc, char *argv[])
{
    MuImage app(argc, argv);

    MainWindow main_window;
    main_window.show();

    return app.exec();
}
