# m17-cxx-demod
M17 Demodulator in C++ (GPL)

This program reads a 48K SPS 16-bit, little-endian, single channel, M17  4-FSK
baseband input stream from STDIN and writes a demodulated/decoded 8K SPS
16-bit, single channel audio stream to STDOUT.

Some diagnostic information is written to STDERR while the demodulator is
running.

## Build

This code requires the codec2-devel package be installed.

    make CXXFLAGS="-std=gnu++17 -O3 $(pkg-config --libs codec2)" m17-demod

## Running

This program was designed to be used with RTL-SDR, specifically rtl-fm.

    rtl_fm -f 144.91M -s 48k | ./m17-demod | play -b 16 -r 8000 -c1 -t s16 -

Note that the oscillators on the PlutoSDR and on most RTL-SDR dongles are
rather inaccurate.  You will need to have both tuned to the same frequency,
correcting for clock inaccuracies on one or both devices.

This was tested using the [m17-gnuradio](https://github.com/mobilinkd/m17-gnuradio)
GNU Radio block feeding an Analog Devices 
[ADALM Pluto SDR](https://www.analog.com/en/design-center/evaluation-hardware-and-software/evaluation-boards-kits/adalm-pluto.html),
modulating the m17.bin file from the
[m17-demodulator](https://github.com/mobilinkd/m17-demodulator) repo.

## Notes

As of now, this is using the older versions of the sync word and LICH
encoding.  It is out of date with the current M17 spec.

## Thanks

Thanks to the M17 team to for the great work on the spec.