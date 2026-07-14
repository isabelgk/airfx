#include "ext.h"

#include "airfx.hpp"
#include "dynamics/buttercomp.hpp"

using TWrapped = airwindohhs::buttercomp::ButterComp<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.buttercomp~", airwindohhs::buttercomp::k_long_description.data());
}
