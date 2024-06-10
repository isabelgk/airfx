#include "c74_min.h"
#include "airfx.hpp"
#include "utility/golem.hpp"

using namespace c74::min;

class golem_tilde : public airfx<golem_tilde, airwindohhs::golem::Golem<double>>
{
    atom m_about_text = symbol{ airwindohhs::golem::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::golem::k_name.data() };
    MIN_TAGS{ airwindohhs::golem::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    golem_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(golem_tilde);
