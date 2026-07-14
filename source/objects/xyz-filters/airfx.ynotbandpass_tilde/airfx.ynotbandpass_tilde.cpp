#include "ext.h"

#include "airfx.hpp"
#include "xyz-filters/ynotbandpass.hpp"

using TWrapped = airwindohhs::ynotbandpass::YNotBandpass<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.ynotbandpass~", airwindohhs::ynotbandpass::k_long_description.data());
}
