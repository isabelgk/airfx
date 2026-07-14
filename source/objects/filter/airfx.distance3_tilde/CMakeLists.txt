set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.distance3_tilde) # output bundle: airfx.distance3~.mxo (_tilde->~)

target_sources(airfx.distance3_tilde
    PRIVATE
        airfx.distance3_tilde.cpp)

target_include_directories(airfx.distance3_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.distance3_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
