set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.flutter_tilde) # output bundle: airfx.flutter~.mxo (_tilde->~)

target_sources(airfx.flutter_tilde
    PRIVATE
        airfx.flutter_tilde.cpp)

target_include_directories(airfx.flutter_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.flutter_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
