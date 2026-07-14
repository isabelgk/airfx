set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.fireamp_tilde) # output bundle: airfx.fireamp~.mxo (_tilde->~)

target_sources(airfx.fireamp_tilde
    PRIVATE
        airfx.fireamp_tilde.cpp)

target_include_directories(airfx.fireamp_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.fireamp_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
