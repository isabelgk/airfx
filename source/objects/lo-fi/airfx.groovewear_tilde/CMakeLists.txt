set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.groovewear_tilde) # output bundle: airfx.groovewear~.mxo (_tilde->~)

target_sources(airfx.groovewear_tilde
    PRIVATE
        airfx.groovewear_tilde.cpp)

target_include_directories(airfx.groovewear_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.groovewear_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
