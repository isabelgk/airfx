#include "ext.h"

#include "airfx.hpp"
#include "utility/dubplate.hpp"

using TWrapped = airwindohhs::dubplate::DubPlate<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.dubplate~", airwindohhs::dubplate::k_long_description.data());
}
