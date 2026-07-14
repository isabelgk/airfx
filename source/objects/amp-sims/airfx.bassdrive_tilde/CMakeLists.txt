set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.bassdrive_tilde) # output bundle: airfx.bassdrive~.mxo (_tilde->~)

target_sources(airfx.bassdrive_tilde
    PRIVATE
        airfx.bassdrive_tilde.cpp)

target_include_directories(airfx.bassdrive_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.bassdrive_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
