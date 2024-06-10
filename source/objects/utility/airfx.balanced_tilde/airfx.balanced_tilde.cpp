#include "c74_min.h"
#include "airfx.hpp"
#include "utility/balanced.hpp"

using namespace c74::min;

class balanced_tilde : public airfx<balanced_tilde, airwindohhs::balanced::Balanced<double>>
{
    atom m_about_text = symbol{ airwindohhs::balanced::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::balanced::k_name.data() };
    MIN_TAGS{ airwindohhs::balanced::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    balanced_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(balanced_tilde);
