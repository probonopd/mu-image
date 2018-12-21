#ifndef SCALECOMMAND_H
#define SCALECOMMAND_H

#include "image.h"


class Scale_command : public QUndoCommand
{
    public:
        Scale_command(Image& image);
        void redo();
        void undo();
    private:
        Image& image;
        QImage old_image;
};

#endif
