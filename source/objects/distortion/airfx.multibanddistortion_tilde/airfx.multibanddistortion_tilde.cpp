#include "ext.h"

#include "airfx.hpp"
#include "distortion/multibanddistortion.hpp"

using TWrapped = airwindohhs::multibanddistortion::MultiBandDistortion<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.multibanddistortion~", airwindohhs::multibanddistortion::k_long_description.data());
}
