#include "ext.h"

#include "airfx.hpp"
#include "amp-sims/leadamp.hpp"

using TWrapped = airwindohhs::leadamp::LeadAmp<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.leadamp~", airwindohhs::leadamp::k_long_description.data());
}
