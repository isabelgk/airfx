#include "c74_min.h"
#include "airfx.hpp"
#include "bass/hermepass.hpp"

using namespace c74::min;

class hermepass_tilde : public airfx<hermepass_tilde, airwindohhs::hermepass::Hermepass<double>>
{
    atom m_about_text = symbol{ airwindohhs::hermepass::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::hermepass::k_name.data() };
    MIN_TAGS{ airwindohhs::hermepass::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    hermepass_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(hermepass_tilde);
