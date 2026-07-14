#include "ext.h"

#include "airfx.hpp"
#include "reverb/kcathedral5.hpp"

using TWrapped = airwindohhs::kcathedral5::kCathedral5<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.kcathedral5~", airwindohhs::kcathedral5::k_long_description.data());
}
