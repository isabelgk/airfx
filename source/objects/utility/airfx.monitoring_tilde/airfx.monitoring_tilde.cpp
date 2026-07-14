#include "ext.h"

#include "airfx.hpp"
#include "utility/monitoring.hpp"

using TWrapped = airwindohhs::monitoring::Monitoring<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.monitoring~", airwindohhs::monitoring::k_long_description.data());
}
