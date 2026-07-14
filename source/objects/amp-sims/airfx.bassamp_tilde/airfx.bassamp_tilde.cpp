#include "ext.h"

#include "airfx.hpp"
#include "amp-sims/bassamp.hpp"

using TWrapped = airwindohhs::bassamp::BassAmp<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.bassamp~", airwindohhs::bassamp::k_long_description.data());
}
