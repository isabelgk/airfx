#include "c74_min.h"
#include "airfx.hpp"
#include "brightness/hypersonx.hpp"

using namespace c74::min;

class hypersonx_tilde : public airfx<hypersonx_tilde, airwindohhs::hypersonx::HypersonX<double>>
{
    atom m_about_text = symbol{ airwindohhs::hypersonx::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::hypersonx::k_name.data() };
    MIN_TAGS{ airwindohhs::hypersonx::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    hypersonx_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(hypersonx_tilde);
