set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.longhand_tilde) # output bundle: airfx.longhand~.mxo (_tilde->~)

target_sources(airfx.longhand_tilde
    PRIVATE
        airfx.longhand_tilde.cpp)

target_include_directories(airfx.longhand_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.longhand_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
