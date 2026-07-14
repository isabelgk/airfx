#include "ext.h"

#include "airfx.hpp"
#include "brightness/slewsonic.hpp"

using TWrapped = airwindohhs::slewsonic::SlewSonic<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.slewsonic~", airwindohhs::slewsonic::k_long_description.data());
}
