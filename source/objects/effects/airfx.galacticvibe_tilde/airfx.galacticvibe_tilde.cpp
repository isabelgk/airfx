#include "c74_min.h"
#include "airfx.hpp"
#include "effects/galacticvibe.hpp"

using namespace c74::min;

class galacticvibe_tilde : public airfx<galacticvibe_tilde, airwindohhs::galacticvibe::GalacticVibe<double>>
{
    atom m_about_text = symbol{ airwindohhs::galacticvibe::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::galacticvibe::k_name.data() };
    MIN_TAGS{ airwindohhs::galacticvibe::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    galacticvibe_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(galacticvibe_tilde);
