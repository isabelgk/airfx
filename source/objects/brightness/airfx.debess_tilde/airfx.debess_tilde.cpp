#include "c74_min.h"
#include "airfx.hpp"
#include "brightness/debess.hpp"

using namespace c74::min;

class debess_tilde : public airfx<debess_tilde, airwindohhs::debess::DeBess<double>>
{
    atom m_about_text = symbol{ airwindohhs::debess::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::debess::k_name.data() };
    MIN_TAGS{ airwindohhs::debess::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    debess_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(debess_tilde);
