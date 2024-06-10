#include "c74_min.h"
#include "airfx.hpp"
#include "utility/purestfade.hpp"

using namespace c74::min;

class purestfade_tilde : public airfx<purestfade_tilde, airwindohhs::purestfade::PurestFade<double>>
{
    atom m_about_text = symbol{ airwindohhs::purestfade::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::purestfade::k_name.data() };
    MIN_TAGS{ airwindohhs::purestfade::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    purestfade_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(purestfade_tilde);
