#include "c74_min.h"
#include "airfx.hpp"
#include "filter/toneslant.hpp"

using namespace c74::min;

class toneslant_tilde : public airfx<toneslant_tilde, airwindohhs::toneslant::ToneSlant<double>>
{
    atom m_about_text = symbol{ airwindohhs::toneslant::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::toneslant::k_name.data() };
    MIN_TAGS{ airwindohhs::toneslant::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    toneslant_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(toneslant_tilde);
