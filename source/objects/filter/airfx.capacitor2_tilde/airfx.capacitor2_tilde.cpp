#include "c74_min.h"
#include "airfx.hpp"
#include "filter/capacitor2.hpp"

using namespace c74::min;

class capacitor2_tilde : public airfx<capacitor2_tilde, airwindohhs::capacitor2::Capacitor2<double>>
{
    atom m_about_text = symbol{ airwindohhs::capacitor2::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::capacitor2::k_name.data() };
    MIN_TAGS{ airwindohhs::capacitor2::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    capacitor2_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(capacitor2_tilde);
