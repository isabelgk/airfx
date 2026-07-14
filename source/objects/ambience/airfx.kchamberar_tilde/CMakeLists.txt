set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.kchamberar_tilde) # output bundle: airfx.kchamberar~.mxo (_tilde->~)

target_sources(airfx.kchamberar_tilde
    PRIVATE
        airfx.kchamberar_tilde.cpp)

target_include_directories(airfx.kchamberar_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.kchamberar_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
