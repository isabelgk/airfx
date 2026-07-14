#include "ext.h"

#include "airfx.hpp"
#include "brightness/platinumslew.hpp"

using TWrapped = airwindohhs::platinumslew::PlatinumSlew<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.platinumslew~", airwindohhs::platinumslew::k_long_description.data());
}
