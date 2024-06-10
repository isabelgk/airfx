#include "c74_min.h"
#include "airfx.hpp"
#include "dynamics/blockparty.hpp"

using namespace c74::min;

class blockparty_tilde : public airfx<blockparty_tilde, airwindohhs::blockparty::BlockParty<double>>
{
    atom m_about_text = symbol{ airwindohhs::blockparty::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::blockparty::k_name.data() };
    MIN_TAGS{ airwindohhs::blockparty::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    blockparty_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(blockparty_tilde);
