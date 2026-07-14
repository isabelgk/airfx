#include "ext.h"

#include "airfx.hpp"
#include "reverb/kcathedral.hpp"

using TWrapped = airwindohhs::kcathedral::kCathedral<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.kcathedral~", airwindohhs::kcathedral::k_long_description.data());
}
