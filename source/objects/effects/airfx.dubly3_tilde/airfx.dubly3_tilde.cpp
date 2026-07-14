#include "ext.h"

#include "airfx.hpp"
#include "effects/dubly3.hpp"

using TWrapped = airwindohhs::dubly3::Dubly3<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.dubly3~", airwindohhs::dubly3::k_long_description.data());
}
