#include "ext.h"

#include "airfx.hpp"
#include "filter/baxandall2.hpp"

using TWrapped = airwindohhs::baxandall2::Baxandall2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.baxandall2~", airwindohhs::baxandall2::k_long_description.data());
}
