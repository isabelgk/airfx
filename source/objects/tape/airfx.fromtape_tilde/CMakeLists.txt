set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.fromtape_tilde) # output bundle: airfx.fromtape~.mxo (_tilde->~)

target_sources(airfx.fromtape_tilde
    PRIVATE
        airfx.fromtape_tilde.cpp)

target_include_directories(airfx.fromtape_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.fromtape_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
