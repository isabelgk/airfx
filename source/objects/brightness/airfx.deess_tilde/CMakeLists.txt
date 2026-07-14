set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.deess_tilde) # output bundle: airfx.deess~.mxo (_tilde->~)

target_sources(airfx.deess_tilde
    PRIVATE
        airfx.deess_tilde.cpp)

target_include_directories(airfx.deess_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.deess_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
