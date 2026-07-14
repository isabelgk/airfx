#include "ext.h"

#include "airfx.hpp"
#include "filter/distance.hpp"

using TWrapped = airwindohhs::distance::Distance<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.distance~", airwindohhs::distance::k_long_description.data());
}
