set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.kcathedral2_tilde) # output bundle: airfx.kcathedral2~.mxo (_tilde->~)

target_sources(airfx.kcathedral2_tilde
    PRIVATE
        airfx.kcathedral2_tilde.cpp)

target_include_directories(airfx.kcathedral2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.kcathedral2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
