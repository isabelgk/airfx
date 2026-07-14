#include "ext.h"

#include "airfx.hpp"
#include "dynamics/dynamics.hpp"

using TWrapped = airwindohhs::dynamics::Dynamics<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.dynamics~", airwindohhs::dynamics::k_long_description.data());
}
