#include "ext.h"

#include "airfx.hpp"
#include "dynamics/pressure5.hpp"

using TWrapped = airwindohhs::pressure5::Pressure5<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.pressure5~", airwindohhs::pressure5::k_long_description.data());
}
