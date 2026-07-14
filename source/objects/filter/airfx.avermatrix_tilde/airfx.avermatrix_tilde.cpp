#include "ext.h"

#include "airfx.hpp"
#include "filter/avermatrix.hpp"

using TWrapped = airwindohhs::avermatrix::AverMatrix<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.avermatrix~", airwindohhs::avermatrix::k_long_description.data());
}
