#include "c74_min.h"
#include "airfx.hpp"
#include "brightness/slewsonic.hpp"

using namespace c74::min;

class slewsonic_tilde : public airfx<slewsonic_tilde, airwindohhs::slewsonic::SlewSonic<double>>
{
    atom m_about_text = symbol{ airwindohhs::slewsonic::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::slewsonic::k_name.data() };
    MIN_TAGS{ airwindohhs::slewsonic::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    slewsonic_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(slewsonic_tilde);
