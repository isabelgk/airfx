set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.lrfliptimer_tilde) # output bundle: airfx.lrfliptimer~.mxo (_tilde->~)

target_sources(airfx.lrfliptimer_tilde
    PRIVATE
        airfx.lrfliptimer_tilde.cpp)

target_include_directories(airfx.lrfliptimer_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.lrfliptimer_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
