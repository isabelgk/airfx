#include "ext.h"

#include "airfx.hpp"
#include "subtlety/phasenudge.hpp"

using TWrapped = airwindohhs::phasenudge::PhaseNudge<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.phasenudge~", airwindohhs::phasenudge::k_long_description.data());
}
