#define SELECT_PIPE(x) pipe* __active_pipe = &x
#define MAKE_PROC __active_pipe->map_managed_processor
#define GET_PROC __active_pipe->get_processor
#define BUF_MAP __active_pipe->assign_ptr_buffer
#define PROC __active_pipe->process_with
#define PROC_IP __active_pipe->process_with_inplace
#define BUF_ALLOC __active_pipe->create_buffer
#define BUF_CP __active_pipe->copy_into
#define SINE_FILL(HZ, TARGET) sine::fill_buffer( HZ, __active_pipe->get_mapped_buffer(TARGET))
#define BUF_MAX(x) __active_pipe->find_max(x)
#define BUF_GAIN_DB(x,db) __active_pipe->multiply_into_scalar(x, volume::db2vol(db), x )
