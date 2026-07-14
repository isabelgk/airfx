set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.tapebias_tilde) # output bundle: airfx.tapebias~.mxo (_tilde->~)

target_sources(airfx.tapebias_tilde
    PRIVATE
        airfx.tapebias_tilde.cpp)

target_include_directories(airfx.tapebias_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.tapebias_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
