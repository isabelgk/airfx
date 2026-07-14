#include "ext.h"

#include "airfx.hpp"
#include "brightness/purestair.hpp"

using TWrapped = airwindohhs::purestair::PurestAir<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.purestair~", airwindohhs::purestair::k_long_description.data());
}
