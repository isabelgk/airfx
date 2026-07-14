#include "ext.h"

#include "airfx.hpp"
#include "amp-sims/cabs.hpp"

using TWrapped = airwindohhs::cabs::Cabs<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.cabs~", airwindohhs::cabs::k_long_description.data());
}
