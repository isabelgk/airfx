set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.subsonly_tilde) # output bundle: airfx.subsonly~.mxo (_tilde->~)

target_sources(airfx.subsonly_tilde
    PRIVATE
        airfx.subsonly_tilde.cpp)

target_include_directories(airfx.subsonly_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.subsonly_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
