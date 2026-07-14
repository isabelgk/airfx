set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.mackeq_tilde) # output bundle: airfx.mackeq~.mxo (_tilde->~)

target_sources(airfx.mackeq_tilde
    PRIVATE
        airfx.mackeq_tilde.cpp)

target_include_directories(airfx.mackeq_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.mackeq_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
