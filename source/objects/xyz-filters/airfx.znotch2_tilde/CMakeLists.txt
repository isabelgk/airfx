set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.znotch2_tilde) # output bundle: airfx.znotch2~.mxo (_tilde->~)

target_sources(airfx.znotch2_tilde
    PRIVATE
        airfx.znotch2_tilde.cpp)

target_include_directories(airfx.znotch2_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.znotch2_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
