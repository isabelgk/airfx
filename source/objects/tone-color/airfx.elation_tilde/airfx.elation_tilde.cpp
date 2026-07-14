#include "ext.h"

#include "airfx.hpp"
#include "tone-color/elation.hpp"

using TWrapped = airwindohhs::elation::Elation<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.elation~", airwindohhs::elation::k_long_description.data());
}
