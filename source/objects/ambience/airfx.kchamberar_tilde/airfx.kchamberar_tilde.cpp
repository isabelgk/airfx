#include "c74_min.h"
#include "airfx.hpp"
#include "ambience/kchamberar.hpp"

using namespace c74::min;

class kchamberar_tilde : public airfx<kchamberar_tilde, airwindohhs::kchamberar::kChamberAR<double>>
{
    atom m_about_text = symbol{ airwindohhs::kchamberar::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::kchamberar::k_name.data() };
    MIN_TAGS{ airwindohhs::kchamberar::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    kchamberar_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(kchamberar_tilde);
