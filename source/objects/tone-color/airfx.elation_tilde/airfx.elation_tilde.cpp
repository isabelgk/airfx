#include "c74_min.h"
#include "airfx.hpp"
#include "tone-color/elation.hpp"

using namespace c74::min;

class elation_tilde : public airfx<elation_tilde, airwindohhs::elation::Elation<double>>
{
    atom m_about_text = symbol{ airwindohhs::elation::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::elation::k_name.data() };
    MIN_TAGS{ airwindohhs::elation::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    elation_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(elation_tilde);
