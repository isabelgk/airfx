set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.cabs2_tilde) # output bundle: airfx.cabs2~.mxo (_tilde->~)

target_sources(airfx.cabs2_tilde
    PRIVATE
        airfx.cabs2_tilde.cpp)

target_include_directories(airfx.cabs2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.cabs2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
