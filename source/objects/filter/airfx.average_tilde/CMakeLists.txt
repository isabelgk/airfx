set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.average_tilde) # output bundle: airfx.average~.mxo (_tilde->~)

target_sources(airfx.average_tilde
    PRIVATE
        airfx.average_tilde.cpp)

target_include_directories(airfx.average_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.average_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
