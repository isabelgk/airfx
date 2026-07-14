set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.pop_tilde) # output bundle: airfx.pop~.mxo (_tilde->~)

target_sources(airfx.pop_tilde
    PRIVATE
        airfx.pop_tilde.cpp)

target_include_directories(airfx.pop_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.pop_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
