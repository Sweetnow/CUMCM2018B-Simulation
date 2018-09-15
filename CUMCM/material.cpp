#include "material.h"

material::material()
{
}

material::material(bool is_one)
{
    if (is_one)
    {
        _type = ONE;
    }
    else
    {
        _type = TWO;
    }
}


material::~material()
{
}

material::state material::get_state()
{
    return _state;
}

void material::set_state(material::state s)
{
    _state = s;
}

bool material::is_one()
{
    return _type == ONE;
}

bool material::is_init()
{
    return _type != NONE;
}


