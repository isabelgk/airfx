#include "ext.h"

#include "airfx.hpp"
#include "filter/distance2.hpp"

using TWrapped = airwindohhs::distance2::Distance2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.distance2~", airwindohhs::distance2::k_long_description.data());
}
