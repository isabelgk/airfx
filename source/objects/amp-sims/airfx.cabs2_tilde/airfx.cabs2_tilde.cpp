#include "ext.h"

#include "airfx.hpp"
#include "amp-sims/cabs2.hpp"

using TWrapped = airwindohhs::cabs2::Cabs2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.cabs2~", airwindohhs::cabs2::k_long_description.data());
}
