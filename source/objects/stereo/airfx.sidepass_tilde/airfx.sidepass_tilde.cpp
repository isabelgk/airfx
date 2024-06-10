#include "c74_min.h"
#include "airfx.hpp"
#include "stereo/sidepass.hpp"

using namespace c74::min;

class sidepass_tilde : public airfx<sidepass_tilde, airwindohhs::sidepass::Sidepass<double>>
{
    atom m_about_text = symbol{ airwindohhs::sidepass::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::sidepass::k_name.data() };
    MIN_TAGS{ airwindohhs::sidepass::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    sidepass_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(sidepass_tilde);
