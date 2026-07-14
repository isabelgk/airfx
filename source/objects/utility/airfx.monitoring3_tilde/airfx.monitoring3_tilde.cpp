#include "ext.h"

#include "airfx.hpp"
#include "utility/monitoring3.hpp"

using TWrapped = airwindohhs::monitoring3::Monitoring3<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.monitoring3~", airwindohhs::monitoring3::k_long_description.data());
}
