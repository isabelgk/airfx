#include "ext.h"

#include "airfx.hpp"
#include "reverb/kcathedral3.hpp"

using TWrapped = airwindohhs::kcathedral3::kCathedral3<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.kcathedral3~", airwindohhs::kcathedral3::k_long_description.data());
}
