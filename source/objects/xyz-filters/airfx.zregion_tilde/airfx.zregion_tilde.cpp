#include "ext.h"

#include "airfx.hpp"
#include "xyz-filters/zregion.hpp"

using TWrapped = airwindohhs::zregion::ZRegion<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.zregion~", airwindohhs::zregion::k_long_description.data());
}
