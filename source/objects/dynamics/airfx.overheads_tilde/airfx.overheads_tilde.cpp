#include "c74_min.h"
#include "airfx.hpp"
#include "dynamics/overheads.hpp"

using namespace c74::min;

class overheads_tilde : public airfx<overheads_tilde, airwindohhs::overheads::Overheads<double>>
{
    atom m_about_text = symbol{ airwindohhs::overheads::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::overheads::k_name.data() };
    MIN_TAGS{ airwindohhs::overheads::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    overheads_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(overheads_tilde);
