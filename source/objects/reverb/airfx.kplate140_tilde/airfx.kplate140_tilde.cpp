#include "ext.h"

#include "airfx.hpp"
#include "reverb/kplate140.hpp"

using TWrapped = airwindohhs::kplate140::kPlate140<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.kplate140~", airwindohhs::kplate140::k_long_description.data());
}
