#include "ext.h"

#include "airfx.hpp"
#include "dynamics/dynamics2.hpp"

using TWrapped = airwindohhs::dynamics2::Dynamics2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.dynamics2~", airwindohhs::dynamics2::k_long_description.data());
}
