#include "ext.h"

#include "airfx.hpp"
#include "dynamics/thunder.hpp"

using TWrapped = airwindohhs::thunder::Thunder<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.thunder~", airwindohhs::thunder::k_long_description.data());
}
