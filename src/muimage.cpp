#include "muimage.h"

#include <QDebug>

MuImage::MuImage(int &argc, char *argv[]) :
    QApplication(argc, argv)
{
	// setAttribute(Qt::AA_EnableHighDpiScaling);
    setApplicationName("mu-image");
    setApplicationVersion("0.1");
}
