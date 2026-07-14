set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.purestwarm_tilde) # output bundle: airfx.purestwarm~.mxo (_tilde->~)

target_sources(airfx.purestwarm_tilde
    PRIVATE
        airfx.purestwarm_tilde.cpp)

target_include_directories(airfx.purestwarm_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.purestwarm_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
