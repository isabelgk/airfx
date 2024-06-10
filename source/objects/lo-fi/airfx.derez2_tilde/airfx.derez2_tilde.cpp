#include "c74_min.h"
#include "airfx.hpp"
#include "lo-fi/derez2.hpp"

using namespace c74::min;

class derez2_tilde : public airfx<derez2_tilde, airwindohhs::derez2::DeRez2<double>>
{
    atom m_about_text = symbol{ airwindohhs::derez2::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::derez2::k_name.data() };
    MIN_TAGS{ airwindohhs::derez2::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    derez2_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(derez2_tilde);
