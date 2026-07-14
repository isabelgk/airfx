set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.toneslant_tilde) # output bundle: airfx.toneslant~.mxo (_tilde->~)

target_sources(airfx.toneslant_tilde
    PRIVATE
        airfx.toneslant_tilde.cpp)

target_include_directories(airfx.toneslant_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.toneslant_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
