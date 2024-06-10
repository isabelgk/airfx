#include "c74_min.h"
#include "airfx.hpp"
#include "lo-fi/groovewear.hpp"

using namespace c74::min;

class groovewear_tilde : public airfx<groovewear_tilde, airwindohhs::groovewear::GrooveWear<double>>
{
    atom m_about_text = symbol{ airwindohhs::groovewear::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::groovewear::k_name.data() };
    MIN_TAGS{ airwindohhs::groovewear::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    groovewear_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(groovewear_tilde);
