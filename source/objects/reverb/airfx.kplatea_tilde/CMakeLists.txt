set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.kplatea_tilde) # output bundle: airfx.kplatea~.mxo (_tilde->~)

target_sources(airfx.kplatea_tilde
    PRIVATE
        airfx.kplatea_tilde.cpp)

target_include_directories(airfx.kplatea_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.kplatea_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
