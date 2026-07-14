#include "ext.h"

#include "airfx.hpp"
#include "effects/cloudcoat.hpp"

using TWrapped = airwindohhs::cloudcoat::CloudCoat<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.cloudcoat~", airwindohhs::cloudcoat::k_long_description.data());
}
