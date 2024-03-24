set(FAASM_USER stream)
function(stream_func exec_name dir_path)
    faasm_func(${exec_name} ${dir_path})
    set(ALL_STREAM_FUNCS ${ALL_STREAM_FUNCS} ${exec_name} PARENT_SCOPE)
endfunction(stream_func)
stream_func(wc_random_source wc_random_source.cpp)
stream_func(wc_split wc_split.cpp)
stream_func(wc_count wc_count.cpp)
# Custom target to group all the stream functions
add_custom_target(stream_all_funcs DEPENDS ${ALL_STREAM_FUNCS})
# Turn on WASM profiling
add_definitions(-DWASM_PROF=1)