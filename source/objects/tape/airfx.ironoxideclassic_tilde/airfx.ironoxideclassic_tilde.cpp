#include "ext.h"

#include "airfx.hpp"
#include "tape/ironoxideclassic.hpp"

using TWrapped = airwindohhs::ironoxideclassic::IronOxideClassic<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.ironoxideclassic~", airwindohhs::ironoxideclassic::k_long_description.data());
}
