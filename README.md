philosophers 42:

1. Only for a 100, basic understanding of mutex and threads, no leaks possible, no bonus

2. When using valgrind --fair-sched=yes --tool=helgrind --history-level=approx : be careful!! this only works for testing:
    1. race conditions
    2. incorrectly use of mutexes
    3. simultaneous writting without protection
if not your program can finish unexpectedly bcs of over use of resources, rememeber hellgrind is a simulation that is checking everything NOT ON REAL TIME.
If u wanna check on real time just use ./philosophers....

3. when using only valgrind be careful with the times. Is also a simulation
