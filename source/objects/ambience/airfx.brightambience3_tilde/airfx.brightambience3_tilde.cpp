#include "ext.h"

#include "airfx.hpp"
#include "ambience/brightambience3.hpp"

using TWrapped = airwindohhs::brightambience3::BrightAmbience3<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.brightambience3~", airwindohhs::brightambience3::k_long_description.data());
}
