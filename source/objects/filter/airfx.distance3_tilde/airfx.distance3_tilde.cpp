#include "ext.h"

#include "airfx.hpp"
#include "filter/distance3.hpp"

using TWrapped = airwindohhs::distance3::Distance3<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.distance3~", airwindohhs::distance3::k_long_description.data());
}
