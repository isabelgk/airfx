#include "ext.h"

#include "airfx.hpp"
#include "filter/pearliteeq.hpp"

using TWrapped = airwindohhs::pearliteeq::PearLiteEQ<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.pearliteeq~", airwindohhs::pearliteeq::k_long_description.data());
}
