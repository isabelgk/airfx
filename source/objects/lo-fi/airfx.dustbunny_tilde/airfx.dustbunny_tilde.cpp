#include "c74_min.h"
#include "airfx.hpp"
#include "lo-fi/dustbunny.hpp"

using namespace c74::min;

class dustbunny_tilde : public airfx<dustbunny_tilde, airwindohhs::dustbunny::DustBunny<double>>
{
    atom m_about_text = symbol{ airwindohhs::dustbunny::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::dustbunny::k_name.data() };
    MIN_TAGS{ airwindohhs::dustbunny::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    dustbunny_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(dustbunny_tilde);
