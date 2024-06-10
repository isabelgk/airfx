#include "c74_min.h"
#include "airfx.hpp"
#include "stereo/wider.hpp"

using namespace c74::min;

class wider_tilde : public airfx<wider_tilde, airwindohhs::wider::Wider<double>>
{
    atom m_about_text = symbol{ airwindohhs::wider::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::wider::k_name.data() };
    MIN_TAGS{ airwindohhs::wider::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    wider_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(wider_tilde);
