//started 500 2 500 16
//esp32 2000, esp8266 500
#define BEDCC_GCAPERGC 200
//how many marks before a sweep
#define BEDCC_GCMPERS 1
#define BED_GCNOREUSE
//sync count sometimes
//#define BEDCC_GCSHASYNC 8192
#define BEDCC_GCSHASYNC 100
//sync do gc moretimes 2 4 8 16 32 64 128
#define BEDCC_GCSSCHECK 16
#define BEDCC_GCRWM 30000
//#define BEDCC_GCRWM 10
//size for heap stack
#define BEDCC_GCHSS 500
//#define BED_GCSTATS
