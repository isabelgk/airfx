#include "c74_min.h"
#include "airfx.hpp"
#include "tone-color/cider.hpp"

using namespace c74::min;

class cider_tilde : public airfx<cider_tilde, airwindohhs::cider::Cider<double>>
{
    atom m_about_text = symbol{ airwindohhs::cider::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::cider::k_name.data() };
    MIN_TAGS{ airwindohhs::cider::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    cider_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(cider_tilde);
