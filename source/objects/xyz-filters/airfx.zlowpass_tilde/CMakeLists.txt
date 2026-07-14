set_property(DIRECTORY PROPERTY max::external YES)
project(airfx.zlowpass_tilde) # output bundle: airfx.zlowpass~.mxo (_tilde->~)

target_sources(airfx.zlowpass_tilde
    PRIVATE
        airfx.zlowpass_tilde.cpp)

target_include_directories(airfx.zlowpass_tilde
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../airfx)

target_link_libraries(airfx.zlowpass_tilde
    PRIVATE
        Airwindohhs::Airwindohhs)
