set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.crickbass_tilde) # output bundle: airfx.crickbass~.mxo (_tilde->~)

target_sources(airfx.crickbass_tilde
    PRIVATE
        airfx.crickbass_tilde.cpp)

target_include_directories(airfx.crickbass_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.crickbass_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
