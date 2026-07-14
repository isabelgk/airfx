#include "ext.h"

#include "airfx.hpp"
#include "xyz-filters/zacidlowpass.hpp"

using TWrapped = airwindohhs::zacidlowpass::ZAcidLowpass<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.zacidlowpass~", airwindohhs::zacidlowpass::k_long_description.data());
}
