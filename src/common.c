#include "common.h"

#ifdef _WIN32
#include <windows.h>
#include <locale.h>
#endif

void init_console_encoding(void) {
#ifdef _WIN32
    SetConsoleCP(936);
    SetConsoleOutputCP(936);
    setlocale(LC_ALL, "chs");
#endif
}

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pause_screen(void) {
    printf("\n按回车键继续...");
    clear_input_buffer();
    getchar();
}

int get_menu_choice(int min, int max) {
    int choice;
    printf("\n请选择: ");
    if (scanf("%d", &choice) != 1) {
        clear_input_buffer();
        return ERROR_INVALID_INPUT;
    }
    clear_input_buffer();
    if (choice < min || choice > max) {
        return ERROR_INVALID_INPUT;
    }
    return choice;
}

void get_current_time(char *buffer, int buffer_size) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(buffer, buffer_size, "%Y-%m-%d %H:%M:%S", tm_info);
}

void generate_id(char *buffer, int buffer_size, const char *prefix) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    snprintf(buffer, buffer_size, "%s%04d%02d%02d%02d%02d", 
             prefix, 
             tm_info->tm_year + 1900, 
             tm_info->tm_mon + 1, 
             tm_info->tm_mday,
             tm_info->tm_hour, 
             tm_info->tm_min);
}
