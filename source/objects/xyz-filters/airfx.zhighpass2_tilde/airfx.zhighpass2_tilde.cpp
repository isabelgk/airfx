#include "c74_min.h"
#include "airfx.hpp"
#include "xyz-filters/zhighpass2.hpp"

using namespace c74::min;

class zhighpass2_tilde : public airfx<zhighpass2_tilde, airwindohhs::zhighpass2::ZHighpass2<double>>
{
    atom m_about_text = symbol{ airwindohhs::zhighpass2::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::zhighpass2::k_name.data() };
    MIN_TAGS{ airwindohhs::zhighpass2::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    zhighpass2_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(zhighpass2_tilde);
