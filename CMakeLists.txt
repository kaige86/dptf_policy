project(dptf)

add_executable(dptf_policy dptf_policy.c policy.c file_utils.c)
#target_compile_options(dptf_policy PRIVATE -g)
