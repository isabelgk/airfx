#include "ext.h"

#include "airfx.hpp"
#include "effects/tremolo.hpp"

using TWrapped = airwindohhs::tremolo::Tremolo<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.tremolo~", airwindohhs::tremolo::k_long_description.data());
}
