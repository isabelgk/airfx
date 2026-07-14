#include "ext.h"

#include "airfx.hpp"
#include "dynamics/stonefirecomp.hpp"

using TWrapped = airwindohhs::stonefirecomp::StoneFireComp<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.stonefirecomp~", airwindohhs::stonefirecomp::k_long_description.data());
}
