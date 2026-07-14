#include "ext.h"

#include "airfx.hpp"
#include "lo-fi/hipcrush.hpp"

using TWrapped = airwindohhs::hipcrush::HipCrush<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.hipcrush~", airwindohhs::hipcrush::k_long_description.data());
}
