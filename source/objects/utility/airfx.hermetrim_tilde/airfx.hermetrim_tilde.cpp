#include "c74_min.h"
#include "airfx.hpp"
#include "utility/hermetrim.hpp"

using namespace c74::min;

class hermetrim_tilde : public airfx<hermetrim_tilde, airwindohhs::hermetrim::HermeTrim<double>>
{
    atom m_about_text = symbol{ airwindohhs::hermetrim::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::hermetrim::k_name.data() };
    MIN_TAGS{ airwindohhs::hermetrim::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    hermetrim_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(hermetrim_tilde);
