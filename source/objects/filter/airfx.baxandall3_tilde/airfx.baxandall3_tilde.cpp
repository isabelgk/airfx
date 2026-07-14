#include "ext.h"

#include "airfx.hpp"
#include "filter/baxandall3.hpp"

using TWrapped = airwindohhs::baxandall3::Baxandall3<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.baxandall3~", airwindohhs::baxandall3::k_long_description.data());
}
