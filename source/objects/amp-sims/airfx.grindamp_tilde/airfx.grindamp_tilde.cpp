#include "ext.h"

#include "airfx.hpp"
#include "amp-sims/grindamp.hpp"

using TWrapped = airwindohhs::grindamp::GrindAmp<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.grindamp~", airwindohhs::grindamp::k_long_description.data());
}
