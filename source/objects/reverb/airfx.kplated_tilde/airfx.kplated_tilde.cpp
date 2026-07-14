#include "ext.h"

#include "airfx.hpp"
#include "reverb/kplated.hpp"

using TWrapped = airwindohhs::kplated::kPlateD<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.kplated~", airwindohhs::kplated::k_long_description.data());
}
