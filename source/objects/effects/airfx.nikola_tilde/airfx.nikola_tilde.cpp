#include "c74_min.h"
#include "airfx.hpp"
#include "effects/nikola.hpp"

using namespace c74::min;

class nikola_tilde : public airfx<nikola_tilde, airwindohhs::nikola::Nikola<double>>
{
    atom m_about_text = symbol{ airwindohhs::nikola::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::nikola::k_name.data() };
    MIN_TAGS{ airwindohhs::nikola::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    nikola_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(nikola_tilde);
