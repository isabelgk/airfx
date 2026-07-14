#include "ext.h"

#include "airfx.hpp"
#include "dynamics/pressure4.hpp"

using TWrapped = airwindohhs::pressure4::Pressure4<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.pressure4~", airwindohhs::pressure4::k_long_description.data());
}
