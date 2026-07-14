#include "ext.h"

#include "airfx.hpp"
#include "brightness/air4.hpp"

using TWrapped = airwindohhs::air4::Air4<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.air4~", airwindohhs::air4::k_long_description.data());
}
