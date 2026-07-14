#include "ext.h"

#include "airfx.hpp"
#include "lo-fi/flutter2.hpp"

using TWrapped = airwindohhs::flutter2::Flutter2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.flutter2~", airwindohhs::flutter2::k_long_description.data());
}
