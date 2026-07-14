#include "ext.h"

#include "airfx.hpp"
#include "lo-fi/cojones.hpp"

using TWrapped = airwindohhs::cojones::Cojones<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.cojones~", airwindohhs::cojones::k_long_description.data());
}
