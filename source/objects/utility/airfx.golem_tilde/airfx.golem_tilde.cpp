#include "ext.h"

#include "airfx.hpp"
#include "utility/golem.hpp"

using TWrapped = airwindohhs::golem::Golem<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.golem~", airwindohhs::golem::k_long_description.data());
}
