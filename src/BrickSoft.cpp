#include "BrickSoft.h"
#include "Brick.h"
#include "ValueGetter.h"

BrickSoft::BrickSoft(ValueGetter& valueGetter) : Brick(valueGetter) 
{
    createBrick(valueGetter.getBrickValuesById("S"));
}
