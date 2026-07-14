#include "ext.h"

#include "airfx.hpp"
#include "utility/dcvoltage.hpp"

using TWrapped = airwindohhs::dcvoltage::DCVoltage<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.dcvoltage~", airwindohhs::dcvoltage::k_long_description.data());
}
