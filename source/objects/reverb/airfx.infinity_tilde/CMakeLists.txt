set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.infinity_tilde) # output bundle: airfx.infinity~.mxo (_tilde->~)

target_sources(airfx.infinity_tilde
    PRIVATE
        airfx.infinity_tilde.cpp)

target_include_directories(airfx.infinity_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.infinity_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
