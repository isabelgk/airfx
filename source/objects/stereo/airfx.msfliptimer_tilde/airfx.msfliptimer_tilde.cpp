#include "ext.h"

#include "airfx.hpp"
#include "stereo/msfliptimer.hpp"

using TWrapped = airwindohhs::msfliptimer::MSFlipTimer<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.msfliptimer~", airwindohhs::msfliptimer::k_long_description.data());
}
