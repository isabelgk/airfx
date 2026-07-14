#include "ext.h"

#include "airfx.hpp"
#include "utility/midside.hpp"

using TWrapped = airwindohhs::midside::MidSide<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.midside~", airwindohhs::midside::k_long_description.data());
}
