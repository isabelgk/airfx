#include "ext.h"

#include "airfx.hpp"
#include "distortion/density3.hpp"

using TWrapped = airwindohhs::density3::Density3<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.density3~", airwindohhs::density3::k_long_description.data());
}
