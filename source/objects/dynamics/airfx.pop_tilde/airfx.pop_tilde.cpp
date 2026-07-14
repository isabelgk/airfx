#include "ext.h"

#include "airfx.hpp"
#include "dynamics/pop.hpp"

using TWrapped = airwindohhs::pop::Pop<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.pop~", airwindohhs::pop::k_long_description.data());
}
