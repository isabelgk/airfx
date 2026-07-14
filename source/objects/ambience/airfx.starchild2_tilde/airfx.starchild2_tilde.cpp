#include "ext.h"

#include "airfx.hpp"
#include "ambience/starchild2.hpp"

using TWrapped = airwindohhs::starchild2::StarChild2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.starchild2~", airwindohhs::starchild2::k_long_description.data());
}
