set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.rawglitters_tilde) # output bundle: airfx.rawglitters~.mxo (_tilde->~)

target_sources(airfx.rawglitters_tilde
    PRIVATE
        airfx.rawglitters_tilde.cpp)

target_include_directories(airfx.rawglitters_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.rawglitters_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
