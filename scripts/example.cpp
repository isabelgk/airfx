#include "c74_min.h"
#include "airfx.hpp"
#include "category/example.hpp"

using namespace c74::min;

class example_tilde : public airfx<example_tilde, airwindohhs::example::Example<double>>
{
    atom m_about_text = symbol{ airwindohhs::example::k_long_description.data() };

  public:
    MIN_DESCRIPTION{ airwindohhs::example::k_name.data() };
    MIN_TAGS{ airwindohhs::example::k_tags.data() };

    message<> m_about{
        this,
        "about",
        description{ "Get the original Airwindows 'about' text for this object" },
        [this](const atoms& args, const int inlet) -> atoms {
            dump_out.send({"about", m_about_text});
            return {};
        }
    };

    example_tilde(const atoms& args = {})
        : airfx(args)
    {
    }
};

MIN_EXTERNAL(example_tilde);
