#ifndef CROPCOMMAND_H
#define CROPCOMMAND_H

#include "image.h"


class Crop_command : public QUndoCommand
{
    public:
        Crop_command(Image& image);
        void redo();
        void undo();
    private:
        Image& image;
        QImage old_image;
};

#endif
