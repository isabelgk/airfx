#include "ext.h"

#include "airfx.hpp"
#include "effects/pitchnasty.hpp"

using TWrapped = airwindohhs::pitchnasty::PitchNasty<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.pitchnasty~", airwindohhs::pitchnasty::k_long_description.data());
}
