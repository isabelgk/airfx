#include "ext.h"

#include "airfx.hpp"
#include "dynamics/bezicomp.hpp"

using TWrapped = airwindohhs::bezicomp::BeziComp<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.bezicomp~", airwindohhs::bezicomp::k_long_description.data());
}
