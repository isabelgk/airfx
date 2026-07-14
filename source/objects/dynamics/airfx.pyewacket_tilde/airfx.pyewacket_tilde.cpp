#include "ext.h"

#include "airfx.hpp"
#include "dynamics/pyewacket.hpp"

using TWrapped = airwindohhs::pyewacket::Pyewacket<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.pyewacket~", airwindohhs::pyewacket::k_long_description.data());
}
