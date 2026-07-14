#include "ext.h"

#include "airfx.hpp"
#include "saturation/hypersoft.hpp"

using TWrapped = airwindohhs::hypersoft::Hypersoft<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.hypersoft~", airwindohhs::hypersoft::k_long_description.data());
}
