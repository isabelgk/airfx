#include "ext.h"

#include "airfx.hpp"
#include "amp-sims/lilamp.hpp"

using TWrapped = airwindohhs::lilamp::LilAmp<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.lilamp~", airwindohhs::lilamp::k_long_description.data());
}
