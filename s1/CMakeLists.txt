# ── ch1 ──
add_executable(s1_env_check ch1/env_check.cpp)

# ── ch2 ──
add_executable(s1_lifetime  ch2/lifetime.cpp)
add_executable(s1_dangling  ch2/dangling.cpp)
add_executable(s1_lifetime2 ch2/lifetime2.cpp)

# ── ch3 ──
add_executable(s1_order        ch3/order.cpp)
add_executable(s1_ex3_1_buffer ch3/ex3_1_buffer.cpp)
add_executable(s1_ex3_5_nested ch3/ex3_5_nested.cpp)

# ── ch4 ──
add_executable(s1_file_raii ch4/file_raii.cpp)
add_executable(s1_save_score_raw ch4/save_score_raw.cpp)
add_executable(s1_scope_timer ch4/scope_timer.cpp)
add_executable(s1_ex4_4_scope_timer ch4/ex4_4_scope_timer.cpp)

# ── ch5 ──
add_executable(s1_unwind ch5/unwind.cpp)
add_executable(s1_ex5_1_no_catch ch5/ex5_1_no_catch.cpp)
add_executable(s1_ex5_2_holder ch5/ex5_2_holder.cpp)
add_executable(s1_ex5_3_two_leak ch5/ex5_3_two_leak.cpp)

# ── ch6 ──
add_executable(s1_shallow ch6/shallow.cpp)
add_executable(s1_ex6_3_half_deep ch6/ex6_3_half_deep.cpp)

# ── ch7 ──
add_executable(s1_ex7_1_wrong_assign ch7/ex7_1_wrong_assign.cpp)
add_executable(s1_ex7_2_fixed_assign ch7/ex7_2_fixed_assign.cpp)
add_executable(s1_ex7_3_exception_wrong ch7/ex7_3_exception_wrong.cpp)
add_executable(s1_ex7_3_exception_swap ch7/ex7_3_exception_swap.cpp)

# ── ch8 ──
add_executable(s1_int_buffer_test ch8/int_buffer_test.cpp)
add_executable(s1_two_fixed ch8/two_fixed.cpp)

# 장마다 실습 파일을 만들 때 한 줄씩 추가
# add_executable(s1_ex2_1_no_delete ch2/ex2_1_no_delete.cpp)
