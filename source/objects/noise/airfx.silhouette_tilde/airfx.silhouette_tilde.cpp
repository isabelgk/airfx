#include "ext.h"

#include "airfx.hpp"
#include "noise/silhouette.hpp"

using TWrapped = airwindohhs::silhouette::Silhouette<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.silhouette~", airwindohhs::silhouette::k_long_description.data());
}
