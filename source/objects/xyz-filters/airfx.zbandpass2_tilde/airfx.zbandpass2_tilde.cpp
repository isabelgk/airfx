#include "ext.h"

#include "airfx.hpp"
#include "xyz-filters/zbandpass2.hpp"

using TWrapped = airwindohhs::zbandpass2::ZBandpass2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.zbandpass2~", airwindohhs::zbandpass2::k_long_description.data());
}
