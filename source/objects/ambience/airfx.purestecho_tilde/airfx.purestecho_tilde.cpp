#include "c74_min.h"
#include "airfx.hpp"
#include "ambience/purestecho.hpp"

using namespace c74::min;

class purestecho_tilde : public airfx<purestecho_tilde, airwindohhs::purestecho::PurestEcho<double>>
{
    atom m_about_text = symbol{ airwindohhs::purestecho::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::purestecho::k_name.data() };
    MIN_TAGS{ airwindohhs::purestecho::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    purestecho_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(purestecho_tilde);
