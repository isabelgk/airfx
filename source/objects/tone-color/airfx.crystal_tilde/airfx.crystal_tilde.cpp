#include "ext.h"

#include "airfx.hpp"
#include "tone-color/crystal.hpp"

using TWrapped = airwindohhs::crystal::Crystal<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.crystal~", airwindohhs::crystal::k_long_description.data());
}
