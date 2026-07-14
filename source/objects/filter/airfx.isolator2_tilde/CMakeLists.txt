set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.isolator2_tilde) # output bundle: airfx.isolator2~.mxo (_tilde->~)

target_sources(airfx.isolator2_tilde
    PRIVATE
        airfx.isolator2_tilde.cpp)

target_include_directories(airfx.isolator2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.isolator2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
