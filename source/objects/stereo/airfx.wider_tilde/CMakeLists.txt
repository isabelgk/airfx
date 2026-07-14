set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.wider_tilde) # output bundle: airfx.wider~.mxo (_tilde->~)

target_sources(airfx.wider_tilde
    PRIVATE
        airfx.wider_tilde.cpp)

target_include_directories(airfx.wider_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.wider_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
