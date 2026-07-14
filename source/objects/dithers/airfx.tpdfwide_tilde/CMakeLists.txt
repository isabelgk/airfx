set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.tpdfwide_tilde) # output bundle: airfx.tpdfwide~.mxo (_tilde->~)

target_sources(airfx.tpdfwide_tilde
    PRIVATE
        airfx.tpdfwide_tilde.cpp)

target_include_directories(airfx.tpdfwide_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.tpdfwide_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
