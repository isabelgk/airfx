set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.sinew_tilde) # output bundle: airfx.sinew~.mxo (_tilde->~)

target_sources(airfx.sinew_tilde
    PRIVATE
        airfx.sinew_tilde.cpp)

target_include_directories(airfx.sinew_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.sinew_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
