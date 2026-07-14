#include "ext.h"

#include "airfx.hpp"
#include "xyz-filters/zregion2.hpp"

using TWrapped = airwindohhs::zregion2::ZRegion2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.zregion2~", airwindohhs::zregion2::k_long_description.data());
}
