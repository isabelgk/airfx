#include "c74_min.h"
#include "airfx.hpp"
#include "utility/rightomono.hpp"

using namespace c74::min;

class rightomono_tilde : public airfx<rightomono_tilde, airwindohhs::rightomono::RightoMono<double>>
{
    atom m_about_text = symbol{ airwindohhs::rightomono::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::rightomono::k_name.data() };
    MIN_TAGS{ airwindohhs::rightomono::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    rightomono_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(rightomono_tilde);
