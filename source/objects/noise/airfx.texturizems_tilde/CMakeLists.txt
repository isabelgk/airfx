set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.texturizems_tilde) # output bundle: airfx.texturizems~.mxo (_tilde->~)

target_sources(airfx.texturizems_tilde
    PRIVATE
        airfx.texturizems_tilde.cpp)

target_include_directories(airfx.texturizems_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.texturizems_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
