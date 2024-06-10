#include "c74_min.h"
#include "airfx.hpp"
#include "lo-fi/deckwrecka.hpp"

using namespace c74::min;

class deckwrecka_tilde : public airfx<deckwrecka_tilde, airwindohhs::deckwrecka::Deckwrecka<double>>
{
    atom m_about_text = symbol{ airwindohhs::deckwrecka::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::deckwrecka::k_name.data() };
    MIN_TAGS{ airwindohhs::deckwrecka::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    deckwrecka_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(deckwrecka_tilde);
