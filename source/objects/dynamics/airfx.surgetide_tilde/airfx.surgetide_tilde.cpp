#include "c74_min.h"
#include "airfx.hpp"
#include "dynamics/surgetide.hpp"

using namespace c74::min;

class surgetide_tilde : public airfx<surgetide_tilde, airwindohhs::surgetide::SurgeTide<double>>
{
    atom m_about_text = symbol{ airwindohhs::surgetide::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::surgetide::k_name.data() };
    MIN_TAGS{ airwindohhs::surgetide::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    surgetide_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(surgetide_tilde);
