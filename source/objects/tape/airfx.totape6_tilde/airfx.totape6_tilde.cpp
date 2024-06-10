#include "c74_min.h"
#include "airfx.hpp"
#include "tape/totape6.hpp"

using namespace c74::min;

class totape6_tilde : public airfx<totape6_tilde, airwindohhs::totape6::ToTape6<double>>
{
    atom m_about_text = symbol{ airwindohhs::totape6::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::totape6::k_name.data() };
    MIN_TAGS{ airwindohhs::totape6::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    totape6_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(totape6_tilde);
