#include "ext.h"

#include "airfx.hpp"
#include "xyz-filters/xregion.hpp"

using TWrapped = airwindohhs::xregion::XRegion<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.xregion~", airwindohhs::xregion::k_long_description.data());
}
