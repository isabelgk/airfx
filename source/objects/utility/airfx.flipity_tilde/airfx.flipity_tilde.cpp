#include "c74_min.h"
#include "airfx.hpp"
#include "utility/flipity.hpp"

using namespace c74::min;

class flipity_tilde : public airfx<flipity_tilde, airwindohhs::flipity::Flipity<double>>
{
    atom m_about_text = symbol{ airwindohhs::flipity::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::flipity::k_name.data() };
    MIN_TAGS{ airwindohhs::flipity::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    flipity_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(flipity_tilde);
