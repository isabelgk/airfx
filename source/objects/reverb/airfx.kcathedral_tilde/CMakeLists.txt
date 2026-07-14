set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.kcathedral_tilde) # output bundle: airfx.kcathedral~.mxo (_tilde->~)

target_sources(airfx.kcathedral_tilde
    PRIVATE
        airfx.kcathedral_tilde.cpp)

target_include_directories(airfx.kcathedral_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.kcathedral_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
