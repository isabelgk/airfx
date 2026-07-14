set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.msfliptimer_tilde) # output bundle: airfx.msfliptimer~.mxo (_tilde->~)

target_sources(airfx.msfliptimer_tilde
    PRIVATE
        airfx.msfliptimer_tilde.cpp)

target_include_directories(airfx.msfliptimer_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.msfliptimer_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
