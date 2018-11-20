#ifndef MUIMAGE_H
#define MUIMAGE_H

#include<QApplication>

class MuImage : public QApplication
{
    Q_OBJECT
public:
    explicit MuImage(int &argc, char *argv[]);
};
#endif
