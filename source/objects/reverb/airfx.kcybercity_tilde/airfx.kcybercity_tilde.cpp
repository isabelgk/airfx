#include "ext.h"

#include "airfx.hpp"
#include "reverb/kcybercity.hpp"

using TWrapped = airwindohhs::kcybercity::kCyberCity<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.kcybercity~", airwindohhs::kcybercity::k_long_description.data());
}
