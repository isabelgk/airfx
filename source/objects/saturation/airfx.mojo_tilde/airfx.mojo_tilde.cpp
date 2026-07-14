#include "ext.h"

#include "airfx.hpp"
#include "saturation/mojo.hpp"

using TWrapped = airwindohhs::mojo::Mojo<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.mojo~", airwindohhs::mojo::k_long_description.data());
}
