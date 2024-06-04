#pragma once
#include "c74_min.h"

using namespace c74::min;

template <typename TWrapper, typename TWrapped>
class airfx : public object<TWrapper>, public vector_operator<>
{
  protected:
    std::unique_ptr<TWrapped> m_wrapped{ std::make_unique<TWrapped>() };
    std::vector<std::unique_ptr<attribute<number, threadsafe::no, limit::clamp>>> m_airfx_parameters{};

  public:
    airfx(const atoms& args)
    {
        auto attributes = this->attributes();
        if (attributes.empty()) {
            for (int i = 0; i < m_wrapped->kNumParameters; i++) {
                auto name = static_cast<std::string>(m_wrapped->get_parameter_name(i));
                m_airfx_parameters.push_back(std::make_unique<attribute<number, threadsafe::no, limit::clamp>>(
                    this,
                    m_wrapped->get_parameter_name(i).data(),
                    m_wrapped->get_parameter_default(i),
                    title{ m_wrapped->get_parameter_title(i).data() },
                    range{ 0.0, 1.0 },
                    setter{ [this, i](const atoms& args, const int inlet) -> atoms {
                        m_wrapped->set_parameter_value(i, args[0]);
                        return {};
                    } },
                    getter{
                        [this, i]() -> atoms {
                            return { m_wrapped->get_parameter_value(i) };
                        } }));

                attributes[name] = dynamic_cast<attribute_base*>(m_airfx_parameters.at(i).get());
            }
        }
    }

#ifdef AIRFX_NO_DOC_GEN
    MIN_FLAGS{ documentation_flags::do_not_generate };
#endif

    MIN_AUTHOR{ "Isabel Kaspriskie" };

    inlet<> in1{ this, "(signal) Input L" };
    inlet<> in2{ this, "(signal) Input R" };
    outlet<> out1{ this, "(signal) Output L", "signal" };
    outlet<> out2{ this, "(signal) Output R", "signal" };

    void operator()(audio_bundle input, audio_bundle output)
    {
        m_wrapped->process(input.samples(), output.samples(), input.frame_count());
    }
};
