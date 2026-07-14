#include "ext.h"

#include "airfx.hpp"
#include "reverb/kbeyond.hpp"

using TWrapped = airwindohhs::kbeyond::kBeyond<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.kbeyond~", airwindohhs::kbeyond::k_long_description.data());
}
