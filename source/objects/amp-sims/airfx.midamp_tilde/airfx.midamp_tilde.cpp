#include "ext.h"

#include "airfx.hpp"
#include "amp-sims/midamp.hpp"

using TWrapped = airwindohhs::midamp::MidAmp<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.midamp~", airwindohhs::midamp::k_long_description.data());
}
