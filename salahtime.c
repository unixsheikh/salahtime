#define _XOPEN_SOURCE
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "salahtime.h"
#include "europe_copenhagen.c"

#define MAX_MINUTES 120
#define MIN_MINUTES -120

/*
 * Global array used between functions for time values that results from time
 * conversion.
 */
static char g_converted_time_string[TIME_STR_SIZE] = "00:00";

void
usage(void)
{
    printf("\nUsage: salahtime [+/-minutes]\n\n");
}

/*
 * This function receives a string representation of a time value like "14:42",
 * it then converts the string into a time tm structure, adds or subtracts a
 * user provided number of minutes, and then converts the time tm structure
 * back to a string.
 *
 * The time_converter function uses the global variable g_converted_time_string
 * for storage.
 */
void
time_converter(const char input_time_string[TIME_STR_SIZE], int add_sub_min)
{
    /*
     * We need some time data for strptime and strftime.
     */
    time_t  time_now = {0};
    struct  tm time_data = *localtime(&time_now);
    char    time_str[TIME_STR_SIZE];

    /*
     * strptime converts a string representation of time to a time tm
     * structure. http://man7.org/linux/man-pages/man3/strptime.3.html
     */
    strptime(input_time_string, "%H:%M", &time_data);

    /*
     * With tm_min we can now add or subtract minutes to the tm structure.
     */
    time_data.tm_min += add_sub_min;

    /*
     * mktime converts the structure it points to into a time_t value.
     */
    mktime(&time_data);

    /*
     * strftime formats the time represented in the time pointer according to
     * the formatting rules defined and the stores the result as a string in
     * a character array.
     *
     * Since we cannot return a pointer to a character array we use the global
     * array to store the new time string which will then be used by the main
     * function.
     */
    strftime(g_converted_time_string, sizeof(time_str), "%H:%M", &time_data);
}

/*
 * Prints the prayer times.
 */
void
display_calendar(const char calendar_array[CALENDAR_SIZE][TIME_STR_SIZE],
    int add_sub_min)
{

    time_t  time_now = {0};
    time(&time_now);

    char    current_day[6], current_date[11], current_time[6];
    struct  tm *tm_data = localtime(&time_now);

    strftime(current_day, 6, "%m-%d", tm_data);
    strftime(current_date, 11, "%d-%m-%Y", tm_data);
    strftime(current_time, 6, "%I:%M", tm_data);

    printf("---------------------");
    printf("\nDate today: %s", current_date);
    printf("\nTime right now: %s", current_time);
    printf("\n---------------------\n");

    int i = 0;

    /* We only iterate over the dates. */
    for (i = 0; i < CALENDAR_SIZE; i = i + 7) {
        if (strstr(calendar_array[i], current_day) != NULL) {

            /*
             * Each time the time_converter function is called the global array
             * g_converted_time_string gets changed to the new value.
             */
            time_converter(calendar_array[i + 6], add_sub_min);
            printf("Fajr:\t\t%s\n", g_converted_time_string);
            time_converter(calendar_array[i + 5], add_sub_min);
            printf("Shuruk:\t\t%s\n", g_converted_time_string);
            time_converter(calendar_array[i + 4], add_sub_min);
            printf("Dhuhr:\t\t%s\n", g_converted_time_string);
            time_converter(calendar_array[i + 3], add_sub_min);
            printf("Asr:\t\t%s\n", g_converted_time_string);
            time_converter(calendar_array[i + 2], add_sub_min);
            printf("Maghrib:\t%s\n", g_converted_time_string);
            time_converter(calendar_array[i + 1], add_sub_min);
            printf("Isha:\t\t%s\n", g_converted_time_string);
        }
    }
}

/*
 * A small command line application that displays the Islamic prayer times for
 * your city (default: Copenhagen, Denmark).
 */
int
main(int argc, char *argv[])
{
    int add_sub_min = 0;

    if (argc > 1 && strcmp(argv[1], "-h") == 0) {
            usage();
            return 0;
    }

    if (argc > 1) {

        /*
         * The atoi function returns the integer representation of a string,
         * so no matter what the user input will be it will either be 0 or some
         * other integer.
         */
        add_sub_min = atoi(argv[1]);

        if (add_sub_min > MAX_MINUTES || add_sub_min < MIN_MINUTES) {
            printf("\nYou have entered an invalid number of minutes!\n\n");
            printf("You can add and subtract between %i and %i minutes\n\n",
                    MAX_MINUTES, MIN_MINUTES);
            return 1;
        }

    }

    display_calendar(europe_copenhagen, add_sub_min);

    return 0;
}
