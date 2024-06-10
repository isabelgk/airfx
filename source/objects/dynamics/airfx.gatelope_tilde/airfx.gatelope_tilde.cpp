#include "c74_min.h"
#include "airfx.hpp"
#include "dynamics/gatelope.hpp"

using namespace c74::min;

class gatelope_tilde : public airfx<gatelope_tilde, airwindohhs::gatelope::Gatelope<double>>
{
    atom m_about_text = symbol{ airwindohhs::gatelope::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::gatelope::k_name.data() };
    MIN_TAGS{ airwindohhs::gatelope::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    gatelope_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(gatelope_tilde);
