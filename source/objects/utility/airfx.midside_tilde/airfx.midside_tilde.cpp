#include "c74_min.h"
#include "airfx.hpp"
#include "utility/midside.hpp"

using namespace c74::min;

class midside_tilde : public airfx<midside_tilde, airwindohhs::midside::MidSide<double>>
{
    atom m_about_text = symbol{ airwindohhs::midside::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::midside::k_name.data() };
    MIN_TAGS{ airwindohhs::midside::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    midside_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(midside_tilde);
