#include "ext.h"

#include "airfx.hpp"
#include "reverb/kcathedral2.hpp"

using TWrapped = airwindohhs::kcathedral2::kCathedral2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.kcathedral2~", airwindohhs::kcathedral2::k_long_description.data());
}
