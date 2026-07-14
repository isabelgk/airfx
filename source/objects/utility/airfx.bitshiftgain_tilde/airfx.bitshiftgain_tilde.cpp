#include "ext.h"

#include "airfx.hpp"
#include "utility/bitshiftgain.hpp"

using TWrapped = airwindohhs::bitshiftgain::BitShiftGain<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.bitshiftgain~", airwindohhs::bitshiftgain::k_long_description.data());
}
