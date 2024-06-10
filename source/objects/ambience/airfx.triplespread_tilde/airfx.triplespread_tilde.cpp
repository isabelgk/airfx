#include "c74_min.h"
#include "airfx.hpp"
#include "ambience/triplespread.hpp"

using namespace c74::min;

class triplespread_tilde : public airfx<triplespread_tilde, airwindohhs::triplespread::TripleSpread<double>>
{
    atom m_about_text = symbol{ airwindohhs::triplespread::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::triplespread::k_name.data() };
    MIN_TAGS{ airwindohhs::triplespread::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    triplespread_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(triplespread_tilde);
