#include "ext.h"

#include "airfx.hpp"
#include "reverb/kplate240.hpp"

using TWrapped = airwindohhs::kplate240::kPlate240<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.kplate240~", airwindohhs::kplate240::k_long_description.data());
}
