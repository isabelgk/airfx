#include "ext.h"

#include "airfx.hpp"
#include "saturation/creature.hpp"

using TWrapped = airwindohhs::creature::Creature<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.creature~", airwindohhs::creature::k_long_description.data());
}
