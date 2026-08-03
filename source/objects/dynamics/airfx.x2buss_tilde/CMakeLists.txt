set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.x2buss_tilde) # output bundle: airfx.x2buss~.mxo (_tilde->~)

target_sources(airfx.x2buss_tilde
    PRIVATE
        airfx.x2buss_tilde.cpp)

target_include_directories(airfx.x2buss_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.x2buss_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
