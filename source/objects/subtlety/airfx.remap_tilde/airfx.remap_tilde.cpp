#include "ext.h"

#include "airfx.hpp"
#include "subtlety/remap.hpp"

using TWrapped = airwindohhs::remap::Remap<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.remap~", airwindohhs::remap::k_long_description.data());
}
