set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.voiceofthestarship_tilde) # output bundle: airfx.voiceofthestarship~.mxo (_tilde->~)

target_sources(airfx.voiceofthestarship_tilde
    PRIVATE
        airfx.voiceofthestarship_tilde.cpp)

target_include_directories(airfx.voiceofthestarship_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.voiceofthestarship_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
