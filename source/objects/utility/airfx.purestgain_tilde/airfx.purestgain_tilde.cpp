#include "ext.h"

#include "airfx.hpp"
#include "utility/purestgain.hpp"

using TWrapped = airwindohhs::purestgain::PurestGain<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.purestgain~", airwindohhs::purestgain::k_long_description.data());
}
