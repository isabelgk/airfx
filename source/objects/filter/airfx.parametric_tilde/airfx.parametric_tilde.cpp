#include "ext.h"

#include "airfx.hpp"
#include "filter/parametric.hpp"

using TWrapped = airwindohhs::parametric::Parametric<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.parametric~", airwindohhs::parametric::k_long_description.data());
}
