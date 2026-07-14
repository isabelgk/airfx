#include "ext.h"

#include "airfx.hpp"
#include "effects/energy.hpp"

using TWrapped = airwindohhs::energy::Energy<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.energy~", airwindohhs::energy::k_long_description.data());
}
