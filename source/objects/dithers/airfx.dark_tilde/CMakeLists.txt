set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.dark_tilde) # output bundle: airfx.dark~.mxo (_tilde->~)

target_sources(airfx.dark_tilde
    PRIVATE
        airfx.dark_tilde.cpp)

target_include_directories(airfx.dark_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.dark_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
