#include "c74_min.h"
#include "airfx.hpp"
#include "brightness/air.hpp"

using namespace c74::min;

class air_tilde : public airfx<air_tilde, airwindohhs::air::Air<double>>
{
    atom m_about_text = symbol{ airwindohhs::air::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::air::k_name.data() };
    MIN_TAGS{ airwindohhs::air::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    air_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(air_tilde);
