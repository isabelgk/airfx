set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.gatelope_tilde) # output bundle: airfx.gatelope~.mxo (_tilde->~)

target_sources(airfx.gatelope_tilde
    PRIVATE
        airfx.gatelope_tilde.cpp)

target_include_directories(airfx.gatelope_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.gatelope_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
