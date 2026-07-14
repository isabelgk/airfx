#include "ext.h"

#include "airfx.hpp"
#include "filter/fateq.hpp"

using TWrapped = airwindohhs::fateq::FatEQ<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.fateq~", airwindohhs::fateq::k_long_description.data());
}
