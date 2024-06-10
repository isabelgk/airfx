#include "c74_min.h"
#include "airfx.hpp"
#include "brightness/deess.hpp"

using namespace c74::min;

class deess_tilde : public airfx<deess_tilde, airwindohhs::deess::DeEss<double>>
{
    atom m_about_text = symbol{ airwindohhs::deess::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::deess::k_name.data() };
    MIN_TAGS{ airwindohhs::deess::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    deess_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(deess_tilde);
