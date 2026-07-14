#include "ext.h"

#include "airfx.hpp"
#include "reverb/kguitarhall.hpp"

using TWrapped = airwindohhs::kguitarhall::kGuitarHall<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.kguitarhall~", airwindohhs::kguitarhall::k_long_description.data());
}
