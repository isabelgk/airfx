#include "ext.h"

#include "airfx.hpp"
#include "lo-fi/chromeoxide.hpp"

using TWrapped = airwindohhs::chromeoxide::ChromeOxide<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.chromeoxide~", airwindohhs::chromeoxide::k_long_description.data());
}
