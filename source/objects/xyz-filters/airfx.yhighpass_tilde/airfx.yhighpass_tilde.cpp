#include "c74_min.h"
#include "airfx.hpp"
#include "xyz-filters/yhighpass.hpp"

using namespace c74::min;

class yhighpass_tilde : public airfx<yhighpass_tilde, airwindohhs::yhighpass::YHighpass<double>>
{
    atom m_about_text = symbol{ airwindohhs::yhighpass::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::yhighpass::k_name.data() };
    MIN_TAGS{ airwindohhs::yhighpass::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    yhighpass_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(yhighpass_tilde);
