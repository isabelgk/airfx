set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.hermepass_tilde) # output bundle: airfx.hermepass~.mxo (_tilde->~)

target_sources(airfx.hermepass_tilde
    PRIVATE
        airfx.hermepass_tilde.cpp)

target_include_directories(airfx.hermepass_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.hermepass_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
