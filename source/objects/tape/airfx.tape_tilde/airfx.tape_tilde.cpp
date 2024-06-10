#include "c74_min.h"
#include "airfx.hpp"
#include "tape/tape.hpp"

using namespace c74::min;

class tape_tilde : public airfx<tape_tilde, airwindohhs::tape::Tape<double>>
{
    atom m_about_text = symbol{ airwindohhs::tape::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::tape::k_name.data() };
    MIN_TAGS{ airwindohhs::tape::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    tape_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(tape_tilde);
