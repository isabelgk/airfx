#include "ext.h"

#include "airfx.hpp"
#include "saturation/tube.hpp"

using TWrapped = airwindohhs::tube::Tube<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.tube~", airwindohhs::tube::k_long_description.data());
}
