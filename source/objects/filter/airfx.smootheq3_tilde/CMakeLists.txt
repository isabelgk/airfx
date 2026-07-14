set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.smootheq3_tilde) # output bundle: airfx.smootheq3~.mxo (_tilde->~)

target_sources(airfx.smootheq3_tilde
    PRIVATE
        airfx.smootheq3_tilde.cpp)

target_include_directories(airfx.smootheq3_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.smootheq3_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
