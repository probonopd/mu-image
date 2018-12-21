#include "cropcommand.h"

#include "image.h"

Crop_command::Crop_command(Image& image)
 : image{image}
{
}

void Crop_command::redo()
{
    old_image = image.get();
    image.crop();
}

void Crop_command::undo()
{
    image.set(old_image);
    image.update_view();
}
