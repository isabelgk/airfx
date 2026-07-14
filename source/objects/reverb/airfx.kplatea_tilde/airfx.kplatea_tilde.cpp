#include "ext.h"

#include "airfx.hpp"
#include "reverb/kplatea.hpp"

using TWrapped = airwindohhs::kplatea::kPlateA<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.kplatea~", airwindohhs::kplatea::k_long_description.data());
}
