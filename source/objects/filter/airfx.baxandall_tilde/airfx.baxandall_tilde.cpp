#include "ext.h"

#include "airfx.hpp"
#include "filter/baxandall.hpp"

using TWrapped = airwindohhs::baxandall::Baxandall<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.baxandall~", airwindohhs::baxandall::k_long_description.data());
}
