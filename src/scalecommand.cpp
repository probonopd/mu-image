#include "scalecommand.h"

#include "image.h"

Scale_command::Scale_command(Image& image)
 : image{image}
{
}

void Scale_command::redo()
{
    old_image = image.get();
    image.scale();
}

void Scale_command::undo()
{
    image.set(old_image);
    image.update_view();
}
