#include "c74_min.h"
#include "airfx.hpp"
#include "filter/subtight.hpp"

using namespace c74::min;

class subtight_tilde : public airfx<subtight_tilde, airwindohhs::subtight::SubTight<double>>
{
    atom m_about_text = symbol{ airwindohhs::subtight::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::subtight::k_name.data() };
    MIN_TAGS{ airwindohhs::subtight::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    subtight_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(subtight_tilde);
