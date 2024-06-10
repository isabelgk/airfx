#include "c74_min.h"
#include "airfx.hpp"
#include "brightness/sinew.hpp"

using namespace c74::min;

class sinew_tilde : public airfx<sinew_tilde, airwindohhs::sinew::Sinew<double>>
{
    atom m_about_text = symbol{ airwindohhs::sinew::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::sinew::k_name.data() };
    MIN_TAGS{ airwindohhs::sinew::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    sinew_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(sinew_tilde);
