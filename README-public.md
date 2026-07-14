# airfx

Max objects ported from the open source VST2 [airwindows](https://github.com/airwindows/airwindows/)
plugins by Chris Johnson, via the [airwindohhs](https://github.com/isabelgk/airwindohhs) C++ port.

Every plugin is available as its own Max object, named `airfx.<plugin>~` (e.g. `airfx.buttercomp~`,
`airfx.galactic~`). Each takes a stereo signal in and out; parameters are exposed as attributes,
settable via the object's inspector or `attr` messages. Send an `about` message to print the
original Airwindows description for that plugin out the object's rightmost outlet.

A multichannel variant of every object is also available as `mc.airfx.<plugin>~`.

## License

This project and the Airwindows VSTs are licensed under the MIT license.
