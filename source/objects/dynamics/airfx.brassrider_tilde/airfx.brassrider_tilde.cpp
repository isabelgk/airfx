#include "ext.h"

#include "airfx.hpp"
#include "dynamics/brassrider.hpp"

using TWrapped = airwindohhs::brassrider::BrassRider<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.brassrider~", airwindohhs::brassrider::k_long_description.data());
}
