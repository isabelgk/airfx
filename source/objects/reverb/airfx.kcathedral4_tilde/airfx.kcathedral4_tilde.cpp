#include "ext.h"

#include "airfx.hpp"
#include "reverb/kcathedral4.hpp"

using TWrapped = airwindohhs::kcathedral4::kCathedral4<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.kcathedral4~", airwindohhs::kcathedral4::k_long_description.data());
}
