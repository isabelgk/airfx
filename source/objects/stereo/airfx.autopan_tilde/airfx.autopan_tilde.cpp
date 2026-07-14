#include "ext.h"

#include "airfx.hpp"
#include "stereo/autopan.hpp"

using TWrapped = airwindohhs::autopan::AutoPan<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.autopan~", airwindohhs::autopan::k_long_description.data());
}
