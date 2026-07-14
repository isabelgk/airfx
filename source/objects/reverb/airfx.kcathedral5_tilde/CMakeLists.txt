set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.kcathedral5_tilde) # output bundle: airfx.kcathedral5~.mxo (_tilde->~)

target_sources(airfx.kcathedral5_tilde
    PRIVATE
        airfx.kcathedral5_tilde.cpp)

target_include_directories(airfx.kcathedral5_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.kcathedral5_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
