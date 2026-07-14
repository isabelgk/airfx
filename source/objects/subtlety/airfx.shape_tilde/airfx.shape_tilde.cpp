#include "ext.h"

#include "airfx.hpp"
#include "subtlety/shape.hpp"

using TWrapped = airwindohhs::shape::Shape<double>;

extern "C" void ext_main(void *r)
{
    airfx::init_class<TWrapped>("airfx.shape~", airwindohhs::shape::k_long_description.data());
}
