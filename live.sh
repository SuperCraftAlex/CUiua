make
watch -n0.2 "cat test.cua | ./cuiua > out.c && ./buildrt.sh && ./out"