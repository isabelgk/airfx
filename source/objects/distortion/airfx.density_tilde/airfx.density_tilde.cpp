#include "ext.h"

#include "airfx.hpp"
#include "distortion/density.hpp"

using TWrapped = airwindohhs::density::Density<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.density~", airwindohhs::density::k_long_description.data());
}
