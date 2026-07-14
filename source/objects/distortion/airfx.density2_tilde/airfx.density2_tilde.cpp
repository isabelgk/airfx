#include "ext.h"

#include "airfx.hpp"
#include "distortion/density2.hpp"

using TWrapped = airwindohhs::density2::Density2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.density2~", airwindohhs::density2::k_long_description.data());
}
