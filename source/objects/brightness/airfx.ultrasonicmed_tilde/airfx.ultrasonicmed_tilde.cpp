#include "c74_min.h"
#include "airfx.hpp"
#include "brightness/ultrasonicmed.hpp"

using namespace c74::min;

class ultrasonicmed_tilde : public airfx<ultrasonicmed_tilde, airwindohhs::ultrasonicmed::UltrasonicMed<double>>
{
    atom m_about_text = symbol{ airwindohhs::ultrasonicmed::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::ultrasonicmed::k_name.data() };
    MIN_TAGS{ airwindohhs::ultrasonicmed::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    ultrasonicmed_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(ultrasonicmed_tilde);
