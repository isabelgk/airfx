#include "ext.h"

#include "airfx.hpp"
#include "xyz-filters/zhighpass.hpp"

using TWrapped = airwindohhs::zhighpass::ZHighpass<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.zhighpass~", airwindohhs::zhighpass::k_long_description.data());
}
