#include "ext.h"

#include "airfx.hpp"
#include "lo-fi/dustbunny.hpp"

using TWrapped = airwindohhs::dustbunny::DustBunny<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.dustbunny~", airwindohhs::dustbunny::k_long_description.data());
}
