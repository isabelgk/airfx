set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.cliponly2_tilde) # output bundle: airfx.cliponly2~.mxo (_tilde->~)

target_sources(airfx.cliponly2_tilde
    PRIVATE
        airfx.cliponly2_tilde.cpp)

target_include_directories(airfx.cliponly2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.cliponly2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
