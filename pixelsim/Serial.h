//
//

#if !defined(Serial__h)
#define Serial__h

class Serial {
public:
    Serial(void);
    void begin(int speed);
    void println(char *s);
    void print(char *s);
    void println(const char *s);
    void print(const char *s);
    void println(unsigned long ul);
    void print(unsigned long ul);

    int lines(void);
    char *get(void);
    void clear(void);
    char **log, *plog;
    int lognr_written, lognr_read;
    void lognr_increase_read(void);
    void lognr_increase_written(void);
};

#endif
