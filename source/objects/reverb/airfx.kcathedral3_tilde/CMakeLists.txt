set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.kcathedral3_tilde) # output bundle: airfx.kcathedral3~.mxo (_tilde->~)

target_sources(airfx.kcathedral3_tilde
    PRIVATE
        airfx.kcathedral3_tilde.cpp)

target_include_directories(airfx.kcathedral3_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.kcathedral3_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
