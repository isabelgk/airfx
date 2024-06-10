#include "c74_min.h"
#include "airfx.hpp"
#include "tone-color/busscolors4.hpp"

using namespace c74::min;

class busscolors4_tilde : public airfx<busscolors4_tilde, airwindohhs::busscolors4::BussColors4<double>>
{
    atom m_about_text = symbol{ airwindohhs::busscolors4::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::busscolors4::k_name.data() };
    MIN_TAGS{ airwindohhs::busscolors4::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    busscolors4_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(busscolors4_tilde);
