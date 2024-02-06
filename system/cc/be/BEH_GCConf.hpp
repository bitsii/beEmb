//started 500 2 500 16
//esp32 2000, esp8266 500
//gc is manual after each run, GCAPER and GCSHASYNC may not matter a lot
//despite best effort the arduino shadow stack / coroutines seem to break gc if it runs while "stuff is going on"
//300 fixed exd issue, was 200
#define BEDCC_GCAPERGC 225
//how many marks before a sweep
#define BEDCC_GCMPERS 1
#define BED_GCNOREUSE
//sync count sometimes
//#define BEDCC_GCSHASYNC 8192
//150 fixed exd issue, was 100
#define BEDCC_GCSHASYNC 125
//sync do gc moretimes 2 4 8 16 32 64 128
#define BEDCC_GCSSCHECK 16
#define BEDCC_GCRWM 30000
//#define BEDCC_GCRWM 10
//size for heap stack
//600 fixed exd issue, was 500, seems like this was only one needed to fix the issue
#define BEDCC_GCHSS 650
//#define BED_GCSTATS
