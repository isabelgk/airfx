#include "ext.h"

#include "airfx.hpp"
#include "distortion/distortion.hpp"

using TWrapped = airwindohhs::distortion::Distortion<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.distortion~", airwindohhs::distortion::k_long_description.data());
}
