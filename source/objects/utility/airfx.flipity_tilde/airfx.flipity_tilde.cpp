#include "ext.h"

#include "airfx.hpp"
#include "utility/flipity.hpp"

using TWrapped = airwindohhs::flipity::Flipity<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.flipity~", airwindohhs::flipity::k_long_description.data());
}
