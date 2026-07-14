#include "ext.h"

#include "airfx.hpp"
#include "filter/holt2.hpp"

using TWrapped = airwindohhs::holt2::Holt2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.holt2~", airwindohhs::holt2::k_long_description.data());
}
