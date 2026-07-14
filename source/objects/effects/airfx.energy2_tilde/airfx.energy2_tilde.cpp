#include "ext.h"

#include "airfx.hpp"
#include "effects/energy2.hpp"

using TWrapped = airwindohhs::energy2::Energy2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.energy2~", airwindohhs::energy2::k_long_description.data());
}
