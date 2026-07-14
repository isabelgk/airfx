set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.spiral2_tilde) # output bundle: airfx.spiral2~.mxo (_tilde->~)

target_sources(airfx.spiral2_tilde
    PRIVATE
        airfx.spiral2_tilde.cpp)

target_include_directories(airfx.spiral2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.spiral2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
