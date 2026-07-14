#include "ext.h"

#include "airfx.hpp"
#include "bass/orbitkick.hpp"

using TWrapped = airwindohhs::orbitkick::OrbitKick<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.orbitkick~", airwindohhs::orbitkick::k_long_description.data());
}
