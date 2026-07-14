#include "ext.h"

#include "airfx.hpp"
#include "stereo/sidedull.hpp"

using TWrapped = airwindohhs::sidedull::SideDull<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.sidedull~", airwindohhs::sidedull::k_long_description.data());
}
