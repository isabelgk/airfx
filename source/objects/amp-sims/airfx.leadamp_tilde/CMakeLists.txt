set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.leadamp_tilde) # output bundle: airfx.leadamp~.mxo (_tilde->~)

target_sources(airfx.leadamp_tilde
    PRIVATE
        airfx.leadamp_tilde.cpp)

target_include_directories(airfx.leadamp_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.leadamp_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
