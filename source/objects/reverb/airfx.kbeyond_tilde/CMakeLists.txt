set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.kbeyond_tilde) # output bundle: airfx.kbeyond~.mxo (_tilde->~)

target_sources(airfx.kbeyond_tilde
    PRIVATE
        airfx.kbeyond_tilde.cpp)

target_include_directories(airfx.kbeyond_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.kbeyond_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
