#include "c74_min.h"
#include "airfx.hpp"
#include "brightness/purestair.hpp"

using namespace c74::min;

class purestair_tilde : public airfx<purestair_tilde, airwindohhs::purestair::PurestAir<double>>
{
    atom m_about_text = symbol{ airwindohhs::purestair::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::purestair::k_name.data() };
    MIN_TAGS{ airwindohhs::purestair::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    purestair_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(purestair_tilde);
