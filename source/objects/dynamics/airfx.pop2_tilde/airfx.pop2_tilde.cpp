#include "c74_min.h"
#include "airfx.hpp"
#include "dynamics/pop2.hpp"

using namespace c74::min;

class pop2_tilde : public airfx<pop2_tilde, airwindohhs::pop2::Pop2<double>>
{
    atom m_about_text = symbol{ airwindohhs::pop2::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::pop2::k_name.data() };
    MIN_TAGS{ airwindohhs::pop2::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    pop2_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(pop2_tilde);
