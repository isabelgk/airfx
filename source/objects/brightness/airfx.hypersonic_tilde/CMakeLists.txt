set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.hypersonic_tilde) # output bundle: airfx.hypersonic~.mxo (_tilde->~)

target_sources(airfx.hypersonic_tilde
    PRIVATE
        airfx.hypersonic_tilde.cpp)

target_include_directories(airfx.hypersonic_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.hypersonic_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
