set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.isolator3_tilde) # output bundle: airfx.isolator3~.mxo (_tilde->~)

target_sources(airfx.isolator3_tilde
    PRIVATE
        airfx.isolator3_tilde.cpp)

target_include_directories(airfx.isolator3_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.isolator3_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
