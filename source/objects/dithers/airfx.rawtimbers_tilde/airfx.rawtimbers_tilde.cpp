#include "c74_min.h"
#include "airfx.hpp"
#include "dithers/rawtimbers.hpp"

using namespace c74::min;

class rawtimbers_tilde : public airfx<rawtimbers_tilde, airwindohhs::rawtimbers::RawTimbers<double>>
{
    atom m_about_text = symbol{ airwindohhs::rawtimbers::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::rawtimbers::k_name.data() };
    MIN_TAGS{ airwindohhs::rawtimbers::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    rawtimbers_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(rawtimbers_tilde);
