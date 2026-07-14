set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.smootheq2_tilde) # output bundle: airfx.smootheq2~.mxo (_tilde->~)

target_sources(airfx.smootheq2_tilde
    PRIVATE
        airfx.smootheq2_tilde.cpp)

target_include_directories(airfx.smootheq2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.smootheq2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
