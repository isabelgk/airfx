#include "ext.h"

#include "airfx.hpp"
#include "filter/mackeq.hpp"

using TWrapped = airwindohhs::mackeq::MackEQ<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.mackeq~", airwindohhs::mackeq::k_long_description.data());
}
