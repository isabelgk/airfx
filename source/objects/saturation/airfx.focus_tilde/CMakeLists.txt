set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.focus_tilde) # output bundle: airfx.focus~.mxo (_tilde->~)

target_sources(airfx.focus_tilde
    PRIVATE
        airfx.focus_tilde.cpp)

target_include_directories(airfx.focus_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.focus_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
