#include "ext.h"

#include "airfx.hpp"
#include "filter/isolator3.hpp"

using TWrapped = airwindohhs::isolator3::Isolator3<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.isolator3~", airwindohhs::isolator3::k_long_description.data());
}
