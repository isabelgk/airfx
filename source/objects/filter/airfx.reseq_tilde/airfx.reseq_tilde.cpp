#include "ext.h"

#include "airfx.hpp"
#include "filter/reseq.hpp"

using TWrapped = airwindohhs::reseq::ResEQ<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.reseq~", airwindohhs::reseq::k_long_description.data());
}
