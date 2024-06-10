#include "c74_min.h"
#include "airfx.hpp"
#include "distortion/loud.hpp"

using namespace c74::min;

class loud_tilde : public airfx<loud_tilde, airwindohhs::loud::Loud<double>>
{
    atom m_about_text = symbol{ airwindohhs::loud::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::loud::k_name.data() };
    MIN_TAGS{ airwindohhs::loud::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    loud_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(loud_tilde);
