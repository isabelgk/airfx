#include "c74_min.h"
#include "airfx.hpp"
#include "lo-fi/pockey.hpp"

using namespace c74::min;

class pockey_tilde : public airfx<pockey_tilde, airwindohhs::pockey::Pockey<double>>
{
    atom m_about_text = symbol{ airwindohhs::pockey::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::pockey::k_name.data() };
    MIN_TAGS{ airwindohhs::pockey::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    pockey_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(pockey_tilde);
