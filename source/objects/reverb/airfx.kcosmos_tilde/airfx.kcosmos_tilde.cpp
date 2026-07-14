#include "ext.h"

#include "airfx.hpp"
#include "reverb/kcosmos.hpp"

using TWrapped = airwindohhs::kcosmos::kCosmos<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.kcosmos~", airwindohhs::kcosmos::k_long_description.data());
}
