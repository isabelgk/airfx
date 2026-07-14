set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.xhighpass_tilde) # output bundle: airfx.xhighpass~.mxo (_tilde->~)

target_sources(airfx.xhighpass_tilde
    PRIVATE
        airfx.xhighpass_tilde.cpp)

target_include_directories(airfx.xhighpass_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.xhighpass_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
