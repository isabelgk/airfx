#include "ext.h"

#include "airfx.hpp"
#include "ambience/pitchdelay.hpp"

using TWrapped = airwindohhs::pitchdelay::PitchDelay<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.pitchdelay~", airwindohhs::pitchdelay::k_long_description.data());
}
