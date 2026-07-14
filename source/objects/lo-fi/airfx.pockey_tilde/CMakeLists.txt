set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.pockey_tilde) # output bundle: airfx.pockey~.mxo (_tilde->~)

target_sources(airfx.pockey_tilde
    PRIVATE
        airfx.pockey_tilde.cpp)

target_include_directories(airfx.pockey_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.pockey_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
