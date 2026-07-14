#include "ext.h"

#include "airfx.hpp"
#include "filter/peareq.hpp"

using TWrapped = airwindohhs::peareq::PearEQ<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.peareq~", airwindohhs::peareq::k_long_description.data());
}
