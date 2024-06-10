#include "c74_min.h"
#include "airfx.hpp"
#include "tape/totape5.hpp"

using namespace c74::min;

class totape5_tilde : public airfx<totape5_tilde, airwindohhs::totape5::ToTape5<double>>
{
    atom m_about_text = symbol{ airwindohhs::totape5::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::totape5::k_name.data() };
    MIN_TAGS{ airwindohhs::totape5::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    totape5_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(totape5_tilde);
