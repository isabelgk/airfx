#include "ext.h"

#include "airfx.hpp"
#include "filter/bezeq.hpp"

using TWrapped = airwindohhs::bezeq::BezEQ<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.bezeq~", airwindohhs::bezeq::k_long_description.data());
}
