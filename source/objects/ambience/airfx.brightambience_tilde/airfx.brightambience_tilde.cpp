#include "ext.h"

#include "airfx.hpp"
#include "ambience/brightambience.hpp"

using TWrapped = airwindohhs::brightambience::BrightAmbience<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.brightambience~", airwindohhs::brightambience::k_long_description.data());
}
