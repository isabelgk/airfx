set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.shortbuss_tilde) # output bundle: airfx.shortbuss~.mxo (_tilde->~)

target_sources(airfx.shortbuss_tilde
    PRIVATE
        airfx.shortbuss_tilde.cpp)

target_include_directories(airfx.shortbuss_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.shortbuss_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
