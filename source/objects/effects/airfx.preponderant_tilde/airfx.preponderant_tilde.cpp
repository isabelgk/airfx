#include "c74_min.h"
#include "airfx.hpp"
#include "effects/preponderant.hpp"

using namespace c74::min;

class preponderant_tilde : public airfx<preponderant_tilde, airwindohhs::preponderant::Preponderant<double>>
{
    atom m_about_text = symbol{ airwindohhs::preponderant::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::preponderant::k_name.data() };
    MIN_TAGS{ airwindohhs::preponderant::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    preponderant_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(preponderant_tilde);
