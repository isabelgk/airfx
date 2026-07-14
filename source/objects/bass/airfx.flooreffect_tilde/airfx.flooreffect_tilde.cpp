#include "ext.h"

#include "airfx.hpp"
#include "bass/floor.hpp"

using TWrapped = airwindohhs::flooreffect::Floor<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.flooreffect~", airwindohhs::flooreffect::k_long_description.data());
}
