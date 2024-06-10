#include "c74_min.h"
#include "airfx.hpp"
#include "dithers/dark.hpp"

using namespace c74::min;

class dark_tilde : public airfx<dark_tilde, airwindohhs::dark::Dark<double>>
{
    atom m_about_text = symbol{ airwindohhs::dark::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::dark::k_name.data() };
    MIN_TAGS{ airwindohhs::dark::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    dark_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(dark_tilde);
