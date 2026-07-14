#include "ext.h"

#include "airfx.hpp"
#include "saturation/spiral2.hpp"

using TWrapped = airwindohhs::spiral2::Spiral2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.spiral2~", airwindohhs::spiral2::k_long_description.data());
}
