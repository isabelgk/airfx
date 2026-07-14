#include "ext.h"

#include "airfx.hpp"
#include "tape/ironoxide5.hpp"

using TWrapped = airwindohhs::ironoxide5::IronOxide5<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.ironoxide5~", airwindohhs::ironoxide5::k_long_description.data());
}
