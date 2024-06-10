#include "c74_min.h"
#include "airfx.hpp"
#include "subtlety/singleendedtriode.hpp"

using namespace c74::min;

class singleendedtriode_tilde : public airfx<singleendedtriode_tilde, airwindohhs::singleendedtriode::SingleEndedTriode<double>>
{
    atom m_about_text = symbol{ airwindohhs::singleendedtriode::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::singleendedtriode::k_name.data() };
    MIN_TAGS{ airwindohhs::singleendedtriode::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    singleendedtriode_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(singleendedtriode_tilde);
