#include "ext.h"

#include "airfx.hpp"
#include "stereo/stereofx.hpp"

using TWrapped = airwindohhs::stereofx::StereoFX<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.stereofx~", airwindohhs::stereofx::k_long_description.data());
}
