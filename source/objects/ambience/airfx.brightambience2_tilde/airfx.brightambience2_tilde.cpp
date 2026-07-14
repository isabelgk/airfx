#include "ext.h"

#include "airfx.hpp"
#include "ambience/brightambience2.hpp"

using TWrapped = airwindohhs::brightambience2::BrightAmbience2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.brightambience2~", airwindohhs::brightambience2::k_long_description.data());
}
