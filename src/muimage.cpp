#include "muimage.h"

#include <QDebug>

MuImage::MuImage(int &argc, char *argv[]) :
    QApplication(argc, argv)
{
    setApplicationName("mu-image");
    setApplicationVersion("0.1");
}
