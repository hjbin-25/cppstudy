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

# 장마다 실습 파일을 만들 때 한 줄씩 추가
# add_executable(s1_ex2_1_no_delete ch2/ex2_1_no_delete.cpp)
