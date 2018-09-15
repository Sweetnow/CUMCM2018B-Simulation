#include "material.h"

int material::_next_id = 1;

material::material()
{
}

material::material(bool is_one)
{
    _material_id = _next_id++;
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

material::state material::get_state() const
{
    return _state;
}

void material::set_state(material::state s)
{
    _state = s;
}

bool material::is_one() const
{
    return _type == ONE;
}

bool material::is_init() const
{
    return _type != NONE;
}

int material::get_id() const
{
    return _material_id;
}


