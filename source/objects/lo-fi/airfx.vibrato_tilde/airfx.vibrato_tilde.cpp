#include "c74_min.h"
#include "airfx.hpp"
#include "lo-fi/vibrato.hpp"

using namespace c74::min;

class vibrato_tilde : public airfx<vibrato_tilde, airwindohhs::vibrato::Vibrato<double>>
{
    atom m_about_text = symbol{ airwindohhs::vibrato::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::vibrato::k_name.data() };
    MIN_TAGS{ airwindohhs::vibrato::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    vibrato_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(vibrato_tilde);
