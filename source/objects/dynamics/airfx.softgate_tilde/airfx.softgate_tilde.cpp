#include "ext.h"

#include "airfx.hpp"
#include "dynamics/softgate.hpp"

using TWrapped = airwindohhs::softgate::SoftGate<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.softgate~", airwindohhs::softgate::k_long_description.data());
}
