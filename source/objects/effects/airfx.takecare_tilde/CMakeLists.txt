set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.takecare_tilde) # output bundle: airfx.takecare~.mxo (_tilde->~)

target_sources(airfx.takecare_tilde
    PRIVATE
        airfx.takecare_tilde.cpp)

target_include_directories(airfx.takecare_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.takecare_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
