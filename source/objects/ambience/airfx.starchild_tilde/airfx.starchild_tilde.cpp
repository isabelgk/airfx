#include "ext.h"

#include "airfx.hpp"
#include "ambience/starchild.hpp"

using TWrapped = airwindohhs::starchild::StarChild<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.starchild~", airwindohhs::starchild::k_long_description.data());
}
