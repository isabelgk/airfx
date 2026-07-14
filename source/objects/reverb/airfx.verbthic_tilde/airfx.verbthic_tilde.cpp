#include "ext.h"

#include "airfx.hpp"
#include "reverb/verbthic.hpp"

using TWrapped = airwindohhs::verbthic::VerbThic<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.verbthic~", airwindohhs::verbthic::k_long_description.data());
}
