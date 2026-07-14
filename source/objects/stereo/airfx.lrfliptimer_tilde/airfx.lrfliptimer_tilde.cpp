#include "ext.h"

#include "airfx.hpp"
#include "stereo/lrfliptimer.hpp"

using TWrapped = airwindohhs::lrfliptimer::LRFlipTimer<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.lrfliptimer~", airwindohhs::lrfliptimer::k_long_description.data());
}
