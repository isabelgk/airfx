#include "c74_min.h"
#include "airfx.hpp"
#include "dithers/paulwide.hpp"

using namespace c74::min;

class paulwide_tilde : public airfx<paulwide_tilde, airwindohhs::paulwide::PaulWide<double>>
{
    atom m_about_text = symbol{ airwindohhs::paulwide::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::paulwide::k_name.data() };
    MIN_TAGS{ airwindohhs::paulwide::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    paulwide_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(paulwide_tilde);
