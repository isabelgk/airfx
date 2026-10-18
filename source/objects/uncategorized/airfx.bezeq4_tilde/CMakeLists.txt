set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.bezeq4_tilde) # output bundle: airfx.bezeq4~.mxo (_tilde->~)

target_sources(airfx.bezeq4_tilde
    PRIVATE
        airfx.bezeq4_tilde.cpp)

target_include_directories(airfx.bezeq4_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.bezeq4_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
