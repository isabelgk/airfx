#include "ext.h"

#include "airfx.hpp"
#include "filter/primefir.hpp"

using TWrapped = airwindohhs::primefir::PrimeFIR<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.primefir~", airwindohhs::primefir::k_long_description.data());
}
