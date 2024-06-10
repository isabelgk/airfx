#include "c74_min.h"
#include "airfx.hpp"
#include "bass/basskit.hpp"

using namespace c74::min;

class basskit_tilde : public airfx<basskit_tilde, airwindohhs::basskit::BassKit<double>>
{
    atom m_about_text = symbol{ airwindohhs::basskit::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::basskit::k_name.data() };
    MIN_TAGS{ airwindohhs::basskit::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    basskit_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(basskit_tilde);
