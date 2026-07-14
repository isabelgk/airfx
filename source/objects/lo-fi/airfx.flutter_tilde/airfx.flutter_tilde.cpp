#include "ext.h"

#include "airfx.hpp"
#include "lo-fi/flutter.hpp"

using TWrapped = airwindohhs::flutter::Flutter<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.flutter~", airwindohhs::flutter::k_long_description.data());
}
