set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.fastdistance_tilde) # output bundle: airfx.fastdistance~.mxo (_tilde->~)

target_sources(airfx.fastdistance_tilde
    PRIVATE
        airfx.fastdistance_tilde.cpp)

target_include_directories(airfx.fastdistance_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.fastdistance_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
