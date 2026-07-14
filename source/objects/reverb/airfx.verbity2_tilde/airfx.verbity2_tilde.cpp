#include "ext.h"

#include "airfx.hpp"
#include "reverb/verbity2.hpp"

using TWrapped = airwindohhs::verbity2::Verbity2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.verbity2~", airwindohhs::verbity2::k_long_description.data());
}
