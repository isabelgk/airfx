#include "c74_min.h"
#include "airfx.hpp"
#include "subtlety/hype.hpp"

using namespace c74::min;

class hype_tilde : public airfx<hype_tilde, airwindohhs::hype::Hype<double>>
{
    atom m_about_text = symbol{ airwindohhs::hype::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::hype::k_name.data() };
    MIN_TAGS{ airwindohhs::hype::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    hype_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(hype_tilde);
