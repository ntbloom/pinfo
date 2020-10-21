#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SYSFS "/sys/class/gpio/gpio"
#define SYS_LEN 50

/* This is a very basic script that reads gpio values using the sysfs interface.
 * Specify pin numbers you are interested as command-line arguments and see the
 * value of the various file descriptors.
 */

int pinfo(int);
char* read_file(const char*);

static int DEBUG = 0;

/* print info about a gpio pin */
int pinfo(int pin) {
    char* fvalue = malloc(SYS_LEN);
    sprintf(fvalue, SYSFS "%d/value", pin);
    char* value = read_file(fvalue);
    free(fvalue);
    if (value == NULL) {
        free(value);
        return EXIT_FAILURE;
    }

    char* fdirection = malloc(SYS_LEN);
    sprintf(fdirection, SYSFS "%d/direction", pin);
    char* direction = read_file(fdirection);
    free(fdirection);

    char* fedge = malloc(SYS_LEN);
    sprintf(fedge, SYSFS "%d/edge", pin);
    char* edge = read_file(fedge);
    free(fedge);

    char* factive = malloc(SYS_LEN);
    sprintf(factive, SYSFS "%d/active_low", pin);
    char* active_low = read_file(factive);
    free(factive);

    printf("Pin %d\n", pin);
    printf("\tdirection: \t%s", direction);
    printf("\tedge: \t\t%s", edge);
    printf("\tvalue: \t\t%s", value);
    printf("\tactive_low: \t%s", active_low);

    free(direction);
    free(edge);
    free(value);
    free(active_low);

    return EXIT_SUCCESS;
}

/* read the value of the file */
char* read_file(const char* fdesc) {
    char* contents = malloc(SYS_LEN);
    FILE* handler = fopen(fdesc, "r");
    if (!handler) {
        if (DEBUG == 1) {
            char* err = malloc(SYS_LEN);
            sprintf(err, "%s", fdesc);
            perror(err);
            free(err);
        }
        free(contents);
        return NULL;
    }
    if (fgets(contents, SYS_LEN, handler) == NULL) {
        perror("fgets");
        free(contents);
        return NULL;
    }
    if (fclose(handler) == EXIT_FAILURE) {
        perror("read_file() fclose error");
        free(contents);
        return NULL;
    }
    return contents;
}

int main(int argc, char* argv[]) {
    /* print all pins if no args given */
    if (argc == 1) {
        int count = 0;
        for (int i = 1; i < 40; i++) {
            if (pinfo(i) == EXIT_SUCCESS) {
                puts("");
                count++;
            }
        }
        if (count == 0) printf("pinfo: no GPIO pins currently exported\n");
        return EXIT_SUCCESS;
    }

    int pin;
    const char* errmsg = "Please provide an integer from 1 to 40\n";
    for (int i = 1; i < argc; i++) {
        pin = atoi(argv[i]);
        if (pin < 1) {
            printf("`pinfo %s`: %s", argv[i], errmsg);
            return EXIT_SUCCESS;
        }
        if (pinfo(pin) != EXIT_SUCCESS) {
            printf("pinfo: gpio pin %d doesn't exist or is not exported\n",
                   pin);
        }
    }
    return EXIT_SUCCESS;
}

