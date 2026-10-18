set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.spiral3_tilde) # output bundle: airfx.spiral3~.mxo (_tilde->~)

target_sources(airfx.spiral3_tilde
    PRIVATE
        airfx.spiral3_tilde.cpp)

target_include_directories(airfx.spiral3_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.spiral3_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
