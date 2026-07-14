#include "ext.h"

#include "airfx.hpp"
#include "reverb/kguitarhall2.hpp"

using TWrapped = airwindohhs::kguitarhall2::kGuitarHall2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.kguitarhall2~", airwindohhs::kguitarhall2::k_long_description.data());
}
