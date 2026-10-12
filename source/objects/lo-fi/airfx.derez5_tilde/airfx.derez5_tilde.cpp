#include "ext.h"

#include "airfx.hpp"
#include "lo-fi/derez5.hpp"

using TWrapped = airwindohhs::derez5::DeRez5<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.derez5~", airwindohhs::derez5::k_long_description.data());
}
