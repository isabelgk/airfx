#include "c74_min.h"
#include "airfx.hpp"
#include "xyz-filters/ynothighpass.hpp"

using namespace c74::min;

class ynothighpass_tilde : public airfx<ynothighpass_tilde, airwindohhs::ynothighpass::YNotHighpass<double>>
{
    atom m_about_text = symbol{ airwindohhs::ynothighpass::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::ynothighpass::k_name.data() };
    MIN_TAGS{ airwindohhs::ynothighpass::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    ynothighpass_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(ynothighpass_tilde);
