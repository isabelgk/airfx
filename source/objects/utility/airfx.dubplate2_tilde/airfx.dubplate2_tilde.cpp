#include "ext.h"

#include "airfx.hpp"
#include "utility/dubplate2.hpp"

using TWrapped = airwindohhs::dubplate2::DubPlate2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.dubplate2~", airwindohhs::dubplate2::k_long_description.data());
}
