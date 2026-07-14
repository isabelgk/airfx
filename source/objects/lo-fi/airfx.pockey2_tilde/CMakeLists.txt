set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.pockey2_tilde) # output bundle: airfx.pockey2~.mxo (_tilde->~)

target_sources(airfx.pockey2_tilde
    PRIVATE
        airfx.pockey2_tilde.cpp)

target_include_directories(airfx.pockey2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.pockey2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
