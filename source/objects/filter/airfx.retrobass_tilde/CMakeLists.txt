set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.retrobass_tilde) # output bundle: airfx.retrobass~.mxo (_tilde->~)

target_sources(airfx.retrobass_tilde
    PRIVATE
        airfx.retrobass_tilde.cpp)

target_include_directories(airfx.retrobass_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.retrobass_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
