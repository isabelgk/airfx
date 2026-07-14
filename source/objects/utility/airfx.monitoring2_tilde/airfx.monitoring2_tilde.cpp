#include "ext.h"

#include "airfx.hpp"
#include "utility/monitoring2.hpp"

using TWrapped = airwindohhs::monitoring2::Monitoring2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.monitoring2~", airwindohhs::monitoring2::k_long_description.data());
}
