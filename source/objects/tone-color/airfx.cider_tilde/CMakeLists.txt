set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.cider_tilde) # output bundle: airfx.cider~.mxo (_tilde->~)

target_sources(airfx.cider_tilde
    PRIVATE
        airfx.cider_tilde.cpp)

target_include_directories(airfx.cider_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.cider_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
