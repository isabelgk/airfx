#include "c74_min.h"
#include "airfx.hpp"
#include "lo-fi/derez.hpp"

using namespace c74::min;

class derez_tilde : public airfx<derez_tilde, airwindohhs::derez::DeRez<double>>
{
    atom m_about_text = symbol{ airwindohhs::derez::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::derez::k_name.data() };
    MIN_TAGS{ airwindohhs::derez::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    derez_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(derez_tilde);
