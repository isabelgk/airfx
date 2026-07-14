#include "ext.h"

#include "airfx.hpp"
#include "dynamics/compresaturator.hpp"

using TWrapped = airwindohhs::compresaturator::Compresaturator<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.compresaturator~", airwindohhs::compresaturator::k_long_description.data());
}
