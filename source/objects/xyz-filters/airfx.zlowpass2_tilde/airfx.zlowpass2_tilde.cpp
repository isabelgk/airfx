#include "ext.h"

#include "airfx.hpp"
#include "xyz-filters/zlowpass2.hpp"

using TWrapped = airwindohhs::zlowpass2::ZLowpass2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.zlowpass2~", airwindohhs::zlowpass2::k_long_description.data());
}
