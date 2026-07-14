#include "ext.h"

#include "airfx.hpp"
#include "ambience/hombre.hpp"

using TWrapped = airwindohhs::hombre::Hombre<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.hombre~", airwindohhs::hombre::k_long_description.data());
}
