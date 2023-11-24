#include "BrickMedium.h"
#include "Brick.h"
#include "ValueGetter.h"

BrickMedium::BrickMedium(ValueGetter& valueGetter) : Brick(valueGetter)
{
    createBrick(valueGetter.getBrickValuesById("M"));
}
