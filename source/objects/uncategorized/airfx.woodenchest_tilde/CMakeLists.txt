set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.woodenchest_tilde) # output bundle: airfx.woodenchest~.mxo (_tilde->~)

target_sources(airfx.woodenchest_tilde
    PRIVATE
        airfx.woodenchest_tilde.cpp)

target_include_directories(airfx.woodenchest_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.woodenchest_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
