#include "ext.h"

#include "airfx.hpp"
#include "ambience/kchamberar.hpp"

using TWrapped = airwindohhs::kchamberar::kChamberAR<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.kchamberar~", airwindohhs::kchamberar::k_long_description.data());
}
