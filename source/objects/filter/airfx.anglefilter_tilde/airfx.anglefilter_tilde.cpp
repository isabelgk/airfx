#include "ext.h"

#include "airfx.hpp"
#include "filter/anglefilter.hpp"

using TWrapped = airwindohhs::anglefilter::AngleFilter<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.anglefilter~", airwindohhs::anglefilter::k_long_description.data());
}
