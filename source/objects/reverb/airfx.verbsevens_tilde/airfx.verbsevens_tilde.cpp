#include "ext.h"

#include "airfx.hpp"
#include "reverb/verbsevens.hpp"

using TWrapped = airwindohhs::verbsevens::VerbSevens<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.verbsevens~", airwindohhs::verbsevens::k_long_description.data());
}
