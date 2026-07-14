#include "ext.h"

#include "airfx.hpp"
#include "dynamics/pop2.hpp"

using TWrapped = airwindohhs::pop2::Pop2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.pop2~", airwindohhs::pop2::k_long_description.data());
}
