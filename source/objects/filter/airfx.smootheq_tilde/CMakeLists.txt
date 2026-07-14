set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.smootheq_tilde) # output bundle: airfx.smootheq~.mxo (_tilde->~)

target_sources(airfx.smootheq_tilde
    PRIVATE
        airfx.smootheq_tilde.cpp)

target_include_directories(airfx.smootheq_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.smootheq_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
