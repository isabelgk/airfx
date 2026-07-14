#include "ext.h"

#include "airfx.hpp"
#include "xyz-filters/zbandpass.hpp"

using TWrapped = airwindohhs::zbandpass::ZBandpass<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.zbandpass~", airwindohhs::zbandpass::k_long_description.data());
}
