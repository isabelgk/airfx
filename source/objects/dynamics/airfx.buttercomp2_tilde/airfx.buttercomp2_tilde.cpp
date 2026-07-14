#include "ext.h"

#include "airfx.hpp"
#include "dynamics/buttercomp2.hpp"

using TWrapped = airwindohhs::buttercomp2::ButterComp2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.buttercomp2~", airwindohhs::buttercomp2::k_long_description.data());
}
