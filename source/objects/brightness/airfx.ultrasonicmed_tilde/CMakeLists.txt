set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.ultrasonicmed_tilde) # output bundle: airfx.ultrasonicmed~.mxo (_tilde->~)

target_sources(airfx.ultrasonicmed_tilde
    PRIVATE
        airfx.ultrasonicmed_tilde.cpp)

target_include_directories(airfx.ultrasonicmed_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.ultrasonicmed_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
