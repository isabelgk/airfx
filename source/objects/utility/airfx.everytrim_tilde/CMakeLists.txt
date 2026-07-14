set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.everytrim_tilde) # output bundle: airfx.everytrim~.mxo (_tilde->~)

target_sources(airfx.everytrim_tilde
    PRIVATE
        airfx.everytrim_tilde.cpp)

target_include_directories(airfx.everytrim_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.everytrim_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
