set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.ynothighpass_tilde) # output bundle: airfx.ynothighpass~.mxo (_tilde->~)

target_sources(airfx.ynothighpass_tilde
    PRIVATE
        airfx.ynothighpass_tilde.cpp)

target_include_directories(airfx.ynothighpass_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.ynothighpass_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
