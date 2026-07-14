#include "ext.h"

#include "airfx.hpp"
#include "saturation/spiral.hpp"

using TWrapped = airwindohhs::spiral::Spiral<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.spiral~", airwindohhs::spiral::k_long_description.data());
}
