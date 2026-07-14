set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.fathomfive_tilde) # output bundle: airfx.fathomfive~.mxo (_tilde->~)

target_sources(airfx.fathomfive_tilde
    PRIVATE
        airfx.fathomfive_tilde.cpp)

target_include_directories(airfx.fathomfive_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.fathomfive_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
