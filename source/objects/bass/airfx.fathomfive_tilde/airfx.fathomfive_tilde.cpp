#include "ext.h"

#include "airfx.hpp"
#include "bass/fathomfive.hpp"

using TWrapped = airwindohhs::fathomfive::FathomFive<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.fathomfive~", airwindohhs::fathomfive::k_long_description.data());
}
