set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.tpdfdither_tilde) # output bundle: airfx.tpdfdither~.mxo (_tilde->~)

target_sources(airfx.tpdfdither_tilde
    PRIVATE
        airfx.tpdfdither_tilde.cpp)

target_include_directories(airfx.tpdfdither_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.tpdfdither_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
