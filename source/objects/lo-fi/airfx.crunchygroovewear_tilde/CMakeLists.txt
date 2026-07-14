set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.crunchygroovewear_tilde) # output bundle: airfx.crunchygroovewear~.mxo (_tilde->~)

target_sources(airfx.crunchygroovewear_tilde
    PRIVATE
        airfx.crunchygroovewear_tilde.cpp)

target_include_directories(airfx.crunchygroovewear_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.crunchygroovewear_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
