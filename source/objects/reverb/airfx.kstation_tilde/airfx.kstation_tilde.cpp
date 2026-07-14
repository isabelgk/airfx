#include "ext.h"

#include "airfx.hpp"
#include "reverb/kstation.hpp"

using TWrapped = airwindohhs::kstation::kStation<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.kstation~", airwindohhs::kstation::k_long_description.data());
}
