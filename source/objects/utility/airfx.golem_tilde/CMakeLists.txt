set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.golem_tilde) # output bundle: airfx.golem~.mxo (_tilde->~)

target_sources(airfx.golem_tilde
    PRIVATE
        airfx.golem_tilde.cpp)

target_include_directories(airfx.golem_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.golem_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
