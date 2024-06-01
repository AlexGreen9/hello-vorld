#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LED_CAPS_LOCK "/sys/class/leds/input2::capslock/brightness"
#define LED_SCROLL_LOCK "/sys/class/leds/input2::scrolllock/brightness"

void set_led_state(const char *led_path, int state) {
    FILE *file = fopen(led_path, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    
    fprintf(file, "%d", state);
    fclose(file);
}

int main() {
    while (1) {
        set_led_state(LED_CAPS_LOCK, 1); // Включить Caps Lock
        set_led_state(LED_SCROLL_LOCK, 1); // Включить Scroll Lock
        sleep(1);
        
        set_led_state(LED_CAPS_LOCK, 0); // Выключить Caps Lock
        set_led_state(LED_SCROLL_LOCK, 0); // Выключить Scroll Lock
        sleep(1);
    }

    return 0;
}

