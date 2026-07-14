#include "ext.h"

#include "airfx.hpp"
#include "amp-sims/fireamp.hpp"

using TWrapped = airwindohhs::fireamp::FireAmp<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.fireamp~", airwindohhs::fireamp::k_long_description.data());
}
