#include "ext.h"

#include "airfx.hpp"
#include "amp-sims/bigamp.hpp"

using TWrapped = airwindohhs::bigamp::BigAmp<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.bigamp~", airwindohhs::bigamp::k_long_description.data());
}
