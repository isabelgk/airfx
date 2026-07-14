#include "ext.h"

#include "airfx.hpp"
#include "utility/decrackle.hpp"

using TWrapped = airwindohhs::decrackle::DeCrackle<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.decrackle~", airwindohhs::decrackle::k_long_description.data());
}
