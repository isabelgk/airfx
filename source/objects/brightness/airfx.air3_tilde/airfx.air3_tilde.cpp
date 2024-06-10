#include "c74_min.h"
#include "airfx.hpp"
#include "brightness/air3.hpp"

using namespace c74::min;

class air3_tilde : public airfx<air3_tilde, airwindohhs::air3::Air3<double>>
{
    atom m_about_text = symbol{ airwindohhs::air3::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::air3::k_name.data() };
    MIN_TAGS{ airwindohhs::air3::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    air3_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(air3_tilde);
