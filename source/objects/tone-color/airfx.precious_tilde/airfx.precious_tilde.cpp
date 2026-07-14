#include "ext.h"

#include "airfx.hpp"
#include "tone-color/precious.hpp"

using TWrapped = airwindohhs::precious::Precious<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.precious~", airwindohhs::precious::k_long_description.data());
}
