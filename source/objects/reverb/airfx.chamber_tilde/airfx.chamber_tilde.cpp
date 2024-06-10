#include "c74_min.h"
#include "airfx.hpp"
#include "reverb/chamber.hpp"

using namespace c74::min;

class chamber_tilde : public airfx<chamber_tilde, airwindohhs::chamber::Chamber<double>>
{
    atom m_about_text = symbol{ airwindohhs::chamber::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::chamber::k_name.data() };
    MIN_TAGS{ airwindohhs::chamber::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    chamber_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(chamber_tilde);
