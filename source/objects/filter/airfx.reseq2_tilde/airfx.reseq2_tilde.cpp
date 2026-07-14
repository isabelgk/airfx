#include "ext.h"

#include "airfx.hpp"
#include "filter/reseq2.hpp"

using TWrapped = airwindohhs::reseq2::ResEQ2<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.reseq2~", airwindohhs::reseq2::k_long_description.data());
}
