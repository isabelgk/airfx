set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.overheads_tilde) # output bundle: airfx.overheads~.mxo (_tilde->~)

target_sources(airfx.overheads_tilde
    PRIVATE
        airfx.overheads_tilde.cpp)

target_include_directories(airfx.overheads_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.overheads_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
