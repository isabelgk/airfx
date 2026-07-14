#include "ext.h"

#include "airfx.hpp"
#include "brightness/ultrasonx.hpp"

using TWrapped = airwindohhs::ultrasonx::UltrasonX<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.ultrasonx~", airwindohhs::ultrasonx::k_long_description.data());
}
