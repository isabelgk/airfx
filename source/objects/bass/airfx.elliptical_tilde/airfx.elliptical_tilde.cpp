#include "ext.h"

#include "airfx.hpp"
#include "bass/elliptical.hpp"

using TWrapped = airwindohhs::elliptical::Elliptical<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.elliptical~", airwindohhs::elliptical::k_long_description.data());
}
