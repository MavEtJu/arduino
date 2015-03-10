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
    void println(signed long sl);
    void print(signed long sl);
    void println(signed short ss);
    void print(signed short ss);
    void println(unsigned short us);
    void print(unsigned short us);
    void println(unsigned int ui);
    void print(unsigned int ui);
    void println(signed int si);
    void print(signed int si);

    int lines(void);
    char *get(void);
    void clear(void);
    char **log, *plog;
    int lognr_written, lognr_read;
    void lognr_increase_read(void);
    void lognr_increase_written(void);
};

#endif
