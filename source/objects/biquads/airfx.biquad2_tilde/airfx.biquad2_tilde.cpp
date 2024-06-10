#include "c74_min.h"
#include "airfx.hpp"
#include "biquads/biquad2.hpp"

using namespace c74::min;

class biquad2_tilde : public airfx<biquad2_tilde, airwindohhs::biquad2::Biquad2<double>>
{
    atom m_about_text = symbol{ airwindohhs::biquad2::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::biquad2::k_name.data() };
    MIN_TAGS{ airwindohhs::biquad2::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    biquad2_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(biquad2_tilde);
