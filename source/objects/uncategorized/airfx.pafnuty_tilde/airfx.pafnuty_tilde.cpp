#include "ext.h"

#include "airfx.hpp"
#include "uncategorized/pafnuty.hpp"

using TWrapped = airwindohhs::pafnuty::Pafnuty<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.pafnuty~", airwindohhs::pafnuty::k_long_description.data());
}
