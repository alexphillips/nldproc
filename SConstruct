Program(
        'nldproc_cliwrap', 
        [
            'src/nldproc_cliwrap.cpp', 
            'src/whitenoise.cpp',
            'src/waveshaper.cpp',
            'src/volume.cpp',
            'src/peakfollower.cpp',
            'src/processor.cpp',
            'src/environment.cpp',
            'src/upmixer.cpp',
            'src/downmixer.cpp',
            'src/pipe.cpp',
            'src/clean_gain.cpp',
        ], 
        LIBS=
        [
            'libDSPFilters'
        ], 
        CPPPATH=
        [
            './DSPFilters/include'
        ], 
        LIBPATH='.',
        CPPFLAGS="-Ofast"
 )

