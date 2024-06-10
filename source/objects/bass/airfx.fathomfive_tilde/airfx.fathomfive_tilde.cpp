#include "c74_min.h"
#include "airfx.hpp"
#include "bass/fathomfive.hpp"

using namespace c74::min;

class fathomfive_tilde : public airfx<fathomfive_tilde, airwindohhs::fathomfive::FathomFive<double>>
{
    atom m_about_text = symbol{ airwindohhs::fathomfive::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::fathomfive::k_name.data() };
    MIN_TAGS{ airwindohhs::fathomfive::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    fathomfive_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(fathomfive_tilde);
