#include "ext.h"

#include "airfx.hpp"
#include "utility/bitshiftpan.hpp"

using TWrapped = airwindohhs::bitshiftpan::BitShiftPan<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.bitshiftpan~", airwindohhs::bitshiftpan::k_long_description.data());
}
