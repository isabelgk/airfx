#include "ext.h"

#include "airfx.hpp"
#include "ambience/clearcoat.hpp"

using TWrapped = airwindohhs::clearcoat::ClearCoat<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.clearcoat~", airwindohhs::clearcoat::k_long_description.data());
}
