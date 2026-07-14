#include "ext.h"

#include "airfx.hpp"
#include "xyz-filters/zlowpass.hpp"

using TWrapped = airwindohhs::zlowpass::ZLowpass<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.zlowpass~", airwindohhs::zlowpass::k_long_description.data());
}
