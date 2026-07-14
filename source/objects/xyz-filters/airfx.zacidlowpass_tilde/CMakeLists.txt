set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.zacidlowpass_tilde) # output bundle: airfx.zacidlowpass~.mxo (_tilde->~)

target_sources(airfx.zacidlowpass_tilde
    PRIVATE
        airfx.zacidlowpass_tilde.cpp)

target_include_directories(airfx.zacidlowpass_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.zacidlowpass_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
