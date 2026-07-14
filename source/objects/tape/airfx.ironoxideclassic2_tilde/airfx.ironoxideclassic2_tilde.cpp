#include "ext.h"

#include "airfx.hpp"
#include "tape/ironoxideclassic2.hpp"

using TWrapped = airwindohhs::ironoxideclassic2::IronOxideClassic2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.ironoxideclassic2~", airwindohhs::ironoxideclassic2::k_long_description.data());
}
