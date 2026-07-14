#include "ext.h"

#include "airfx.hpp"
#include "utility/contenthided.hpp"

using TWrapped = airwindohhs::contenthided::ContentHideD<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.contenthided~", airwindohhs::contenthided::k_long_description.data());
}
