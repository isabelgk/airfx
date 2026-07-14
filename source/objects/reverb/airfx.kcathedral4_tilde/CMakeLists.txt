set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.kcathedral4_tilde) # output bundle: airfx.kcathedral4~.mxo (_tilde->~)

target_sources(airfx.kcathedral4_tilde
    PRIVATE
        airfx.kcathedral4_tilde.cpp)

target_include_directories(airfx.kcathedral4_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.kcathedral4_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
