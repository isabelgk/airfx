#include "ext.h"

#include "airfx.hpp"
#include "reverb/verbity.hpp"

using TWrapped = airwindohhs::verbity::Verbity<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.verbity~", airwindohhs::verbity::k_long_description.data());
}
