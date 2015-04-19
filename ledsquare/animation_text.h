#ifndef animations_text__h
#define animations_text__h

#include "LED_Animation.h"
#include "LED_Text.h"
#include "A_Tools.h"

class LED_quickbrownfox1 : public LED_Animation {
public:
    MYOWNCONSTRUCTOR(LED_quickbrownfox1);
    ~LED_quickbrownfox1(void);
    void animation(void);
    LED_Text *text;
};

#endif
