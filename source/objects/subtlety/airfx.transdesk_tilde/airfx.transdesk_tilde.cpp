#include "c74_min.h"
#include "airfx.hpp"
#include "subtlety/transdesk.hpp"

using namespace c74::min;

class transdesk_tilde : public airfx<transdesk_tilde, airwindohhs::transdesk::TransDesk<double>>
{
    atom m_about_text = symbol{ airwindohhs::transdesk::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::transdesk::k_name.data() };
    MIN_TAGS{ airwindohhs::transdesk::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    transdesk_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(transdesk_tilde);
