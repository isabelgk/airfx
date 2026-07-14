#include "ext.h"

#include "airfx.hpp"
#include "xyz-filters/xbandpass.hpp"

using TWrapped = airwindohhs::xbandpass::XBandpass<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.xbandpass~", airwindohhs::xbandpass::k_long_description.data());
}
