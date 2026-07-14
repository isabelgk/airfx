#include "ext.h"

#include "airfx.hpp"
#include "dynamics/pressure6.hpp"

using TWrapped = airwindohhs::pressure6::Pressure6<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.pressure6~", airwindohhs::pressure6::k_long_description.data());
}
