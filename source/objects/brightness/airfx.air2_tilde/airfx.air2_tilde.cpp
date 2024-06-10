#include "c74_min.h"
#include "airfx.hpp"
#include "brightness/air2.hpp"

using namespace c74::min;

class air2_tilde : public airfx<air2_tilde, airwindohhs::air2::Air2<double>>
{
    atom m_about_text = symbol{ airwindohhs::air2::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::air2::k_name.data() };
    MIN_TAGS{ airwindohhs::air2::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    air2_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(air2_tilde);
