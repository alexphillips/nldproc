#pragma once
#include "processor.h"
#include "fir.h"
#include "environment.h"

namespace nldproc {
    class rms : public processor {
        public:
            rms();
            void configure(time_ms window_size);
            buffer_chunksize get_filter_size();
            rms(time_ms window_size);
            ~rms();
            virtual latency_samples get_latency();
        private:
            virtual void process_channel( channel_index channel, single_channel input, single_channel output );
            sample* history; 
            sample* window;
            buffer_chunksize filter_size;
    };
}
