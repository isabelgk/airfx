#include "ext.h"

#include "airfx.hpp"
#include "effects/dubly2.hpp"

using TWrapped = airwindohhs::dubly2::Dubly2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.dubly2~", airwindohhs::dubly2::k_long_description.data());
}
