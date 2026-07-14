#include "ext.h"

#include "airfx.hpp"
#include "dynamics/dynamics3.hpp"

using TWrapped = airwindohhs::dynamics3::Dynamics3<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.dynamics3~", airwindohhs::dynamics3::k_long_description.data());
}
