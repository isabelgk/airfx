set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.starchild_tilde) # output bundle: airfx.starchild~.mxo (_tilde->~)

target_sources(airfx.starchild_tilde
    PRIVATE
        airfx.starchild_tilde.cpp)

target_include_directories(airfx.starchild_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.starchild_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
