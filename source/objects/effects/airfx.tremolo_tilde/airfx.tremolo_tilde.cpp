#include "c74_min.h"
#include "airfx.hpp"
#include "effects/tremolo.hpp"

using namespace c74::min;

class tremolo_tilde : public airfx<tremolo_tilde, airwindohhs::tremolo::Tremolo<double>>
{
    atom m_about_text = symbol{ airwindohhs::tremolo::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::tremolo::k_name.data() };
    MIN_TAGS{ airwindohhs::tremolo::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    tremolo_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(tremolo_tilde);
