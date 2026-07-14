#include "ext.h"

#include "airfx.hpp"
#include "dithers/doublepaul.hpp"

using TWrapped = airwindohhs::doublepaul::DoublePaul<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.doublepaul~", airwindohhs::doublepaul::k_long_description.data());
}
