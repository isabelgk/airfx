#include "ext.h"

#include "airfx.hpp"
#include "stereo/sweetwide.hpp"

using TWrapped = airwindohhs::sweetwide::SweetWide<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.sweetwide~", airwindohhs::sweetwide::k_long_description.data());
}
