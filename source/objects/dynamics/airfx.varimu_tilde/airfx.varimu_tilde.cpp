#include "ext.h"

#include "airfx.hpp"
#include "dynamics/varimu.hpp"

using TWrapped = airwindohhs::varimu::VariMu<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.varimu~", airwindohhs::varimu::k_long_description.data());
}
