#include "c74_min.h"
#include "airfx.hpp"
#include "lo-fi/bitglitter.hpp"

using namespace c74::min;

class bitglitter_tilde : public airfx<bitglitter_tilde, airwindohhs::bitglitter::BitGlitter<double>>
{
    atom m_about_text = symbol{ airwindohhs::bitglitter::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::bitglitter::k_name.data() };
    MIN_TAGS{ airwindohhs::bitglitter::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    bitglitter_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(bitglitter_tilde);
