set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.yhighpass_tilde) # output bundle: airfx.yhighpass~.mxo (_tilde->~)

target_sources(airfx.yhighpass_tilde
    PRIVATE
        airfx.yhighpass_tilde.cpp)

target_include_directories(airfx.yhighpass_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.yhighpass_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
