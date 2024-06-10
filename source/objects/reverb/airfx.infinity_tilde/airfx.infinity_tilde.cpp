#include "c74_min.h"
#include "airfx.hpp"
#include "reverb/infinity.hpp"

using namespace c74::min;

class infinity_tilde : public airfx<infinity_tilde, airwindohhs::infinity::Infinity<double>>
{
    atom m_about_text = symbol{ airwindohhs::infinity::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::infinity::k_name.data() };
    MIN_TAGS{ airwindohhs::infinity::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    infinity_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(infinity_tilde);
