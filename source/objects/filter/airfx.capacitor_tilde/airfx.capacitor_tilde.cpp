#include "c74_min.h"
#include "airfx.hpp"
#include "filter/capacitor.hpp"

using namespace c74::min;

class capacitor_tilde : public airfx<capacitor_tilde, airwindohhs::capacitor::Capacitor<double>>
{
    atom m_about_text = symbol{ airwindohhs::capacitor::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::capacitor::k_name.data() };
    MIN_TAGS{ airwindohhs::capacitor::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    capacitor_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(capacitor_tilde);
