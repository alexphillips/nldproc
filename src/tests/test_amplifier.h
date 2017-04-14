int test_amplifier() {

    environment::configure_test_environment( (frequency_hz)44100, (sample_count)44100*3 ); 

    pipe            test_pipe;          
    stereo_buffer   master_buffer = test_pipe.create_unmapped_buffer(); 
    amplifier       test_amplifier;

    file::unsafe_fill_from_file(  NLDPROC_TEST_RAW_AUDIO_FILE, master_buffer );
    test_pipe.assign_ptr_buffer( {"buf:master"}, master_buffer );
    test_pipe.map_processor( &test_amplifier, {"proc:amplifier"} );

    //create a gain param, mapped to the gainVol control on the
    //amplifier processor, converting a dB input to a linear amplitude
    
    test_pipe.create_parameter( 
            "param:gain(dB)", (parameter_dispatches){ 
                {
                    [](double dB) { return volume::db2vol(dB); },
                    test_pipe.get_control( "proc:amplifier", "control:gainVol" )
                } 
            }
    );

    test_pipe.set_parameter("param:gain(dB)", 3 );

    test::write_input_signal_test_data( &test_pipe, "buf:master");
    test_pipe.process_with_inplace( "proc:amplifier", "buf:master" );

    // write test report info to file 
    test::write_mono_test_data( &test_pipe, "buf:master", NLDPROC_FFT_LIMITS(10,20000) );

    return NLDPROC_TEST_SUCCESS;
}
