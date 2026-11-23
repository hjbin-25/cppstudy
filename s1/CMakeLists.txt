# ── ch1 ──
add_executable(s1_env_check ch1/env_check.cpp)

# ── ch2 ──
add_executable(s1_lifetime  ch2/lifetime.cpp)
add_executable(s1_dangling  ch2/dangling.cpp)
add_executable(s1_lifetime2 ch2/lifetime2.cpp)

# 장마다 실습 파일을 만들 때 한 줄씩 추가
# add_executable(s1_ex2_1_no_delete ch2/ex2_1_no_delete.cpp)
