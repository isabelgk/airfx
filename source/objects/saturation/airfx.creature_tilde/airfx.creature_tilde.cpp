#include "c74_min.h"
#include "airfx.hpp"
#include "saturation/creature.hpp"

using namespace c74::min;

class creature_tilde : public airfx<creature_tilde, airwindohhs::creature::Creature<double>>
{
    atom m_about_text = symbol{ airwindohhs::creature::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::creature::k_name.data() };
    MIN_TAGS{ airwindohhs::creature::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    creature_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(creature_tilde);
