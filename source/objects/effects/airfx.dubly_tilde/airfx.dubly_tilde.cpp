#include "ext.h"

#include "airfx.hpp"
#include "effects/dubly.hpp"

using TWrapped = airwindohhs::dubly::Dubly<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.dubly~", airwindohhs::dubly::k_long_description.data());
}
