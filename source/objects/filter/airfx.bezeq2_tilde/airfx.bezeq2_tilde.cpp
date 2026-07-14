#include "ext.h"

#include "airfx.hpp"
#include "filter/bezeq2.hpp"

using TWrapped = airwindohhs::bezeq2::BezEQ2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.bezeq2~", airwindohhs::bezeq2::k_long_description.data());
}
