#include "ext.h"

#include "airfx.hpp"
#include "dynamics/surge.hpp"

using TWrapped = airwindohhs::surge::Surge<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.surge~", airwindohhs::surge::k_long_description.data());
}
