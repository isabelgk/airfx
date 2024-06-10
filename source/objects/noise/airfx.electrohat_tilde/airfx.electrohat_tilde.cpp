#include "c74_min.h"
#include "airfx.hpp"
#include "noise/electrohat.hpp"

using namespace c74::min;

class electrohat_tilde : public airfx<electrohat_tilde, airwindohhs::electrohat::ElectroHat<double>>
{
    atom m_about_text = symbol{ airwindohhs::electrohat::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::electrohat::k_name.data() };
    MIN_TAGS{ airwindohhs::electrohat::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    electrohat_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(electrohat_tilde);
