#include "c74_min.h"
#include "airfx.hpp"
#include "subtlety/inflamer.hpp"

using namespace c74::min;

class inflamer_tilde : public airfx<inflamer_tilde, airwindohhs::inflamer::Inflamer<double>>
{
    atom m_about_text = symbol{ airwindohhs::inflamer::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::inflamer::k_name.data() };
    MIN_TAGS{ airwindohhs::inflamer::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    inflamer_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(inflamer_tilde);
