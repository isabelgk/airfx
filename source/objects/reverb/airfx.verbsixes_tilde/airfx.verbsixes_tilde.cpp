#include "ext.h"

#include "airfx.hpp"
#include "reverb/verbsixes.hpp"

using TWrapped = airwindohhs::verbsixes::VerbSixes<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.verbsixes~", airwindohhs::verbsixes::k_long_description.data());
}
