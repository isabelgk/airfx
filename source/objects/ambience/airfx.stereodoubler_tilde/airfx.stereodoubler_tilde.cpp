#include "c74_min.h"
#include "airfx.hpp"
#include "ambience/stereodoubler.hpp"

using namespace c74::min;

class stereodoubler_tilde : public airfx<stereodoubler_tilde, airwindohhs::stereodoubler::StereoDoubler<double>>
{
    atom m_about_text = symbol{ airwindohhs::stereodoubler::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::stereodoubler::k_name.data() };
    MIN_TAGS{ airwindohhs::stereodoubler::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    stereodoubler_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(stereodoubler_tilde);
