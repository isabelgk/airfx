#include "c74_min.h"
#include "airfx.hpp"
#include "dynamics/pop.hpp"

using namespace c74::min;

class pop_tilde : public airfx<pop_tilde, airwindohhs::pop::Pop<double>>
{
    atom m_about_text = symbol{ airwindohhs::pop::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::pop::k_name.data() };
    MIN_TAGS{ airwindohhs::pop::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    pop_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(pop_tilde);
