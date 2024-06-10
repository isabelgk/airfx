#include "c74_min.h"
#include "airfx.hpp"
#include "tone-color/precious.hpp"

using namespace c74::min;

class precious_tilde : public airfx<precious_tilde, airwindohhs::precious::Precious<double>>
{
    atom m_about_text = symbol{ airwindohhs::precious::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::precious::k_name.data() };
    MIN_TAGS{ airwindohhs::precious::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    precious_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(precious_tilde);
