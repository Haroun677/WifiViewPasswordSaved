#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_PROFILES 100
#define MAX_NAME 128

char profiles[MAX_PROFILES][MAX_NAME];
int profile_count = 0;

void set_color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void clear_screen() {
    system("cls");
}

void banner() {
    set_color(11);
    printf("\n");
    printf("  $$\\   $$\\                                                   \n");
    printf("  $$ |  $$ |                                                  \n");
    printf("  $$ |  $$ | $$$$$$\\   $$$$$$\\   $$$$$$\\  $$\\   $$\\ $$$$$$$\\  \n");
    printf("  $$$$$$$$ | \\____$$\\ $$  __$$\\ $$  __$$\\ $$ |  $$ |$$  __$$\\ \n");
    printf("  $$  __$$ | $$$$$$$ |$$ |  \\__|$$ /  $$ |$$ |  $$ |$$ |  $$ |\n");
    printf("  $$ |  $$ |$$  __$$ |$$ |      $$ |  $$ |$$ |  $$ |$$ |  $$ |\n");
    printf("  $$ |  $$ |\\$$$$$$$ |$$ |      \\$$$$$$  |\\$$$$$$  |$$ |  $$ |\n");
    printf("  \\__|  \\__| \\_______||\\__|       \\______/  \\______/ \\__|  \\__|\n");
    printf("\n");

    set_color(14);
    printf("  +------------------------------------------+\n");
    printf("  |  ");
    set_color(10);
    printf(">>> This created by Haroun <<<");
    set_color(14);
    printf("          |\n");
    printf("  |        ");
    set_color(11);
    printf("WiFi Password Viewer v1.0");
    set_color(14);
    printf("       |\n");
    printf("  +------------------------------------------+\n\n");
}

void load_profiles() {
    FILE *fp;
    char line[256];
    profile_count = 0;

    fp = popen("netsh wlan show profiles", "r");
    if (!fp) return;

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "All User Profile")) {
            char *p = strstr(line, ": ");
            if (p) {
                p += 2;
                strncpy(profiles[profile_count], p, MAX_NAME);
                profiles[profile_count][strcspn(profiles[profile_count], "\r\n")] = 0;
                profile_count++;
            }
        }
    }
    pclose(fp);
}

void show_password(const char *profile_name) {
    char command[512];
    char line[256];

    snprintf(command, sizeof(command),
        "netsh wlan show profile name=\"%s\" key=clear", profile_name);

    FILE *fp = popen(command, "r");
    if (!fp) return;

    int found = 0;
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "Key Content")) {
            char *pass = strstr(line, ": ");
            if (pass) {
                pass += 2;
                pass[strcspn(pass, "\r\n")] = 0;
                set_color(10);
                printf("  [PASSWORD] : ");
                set_color(15);
                printf("%s\n", pass);
                found = 1;
            }
        }
    }
    pclose(fp);

    if (!found) {
        set_color(8);
        printf("  [PASSWORD] : (no password / open network)\n");
    }
}

void show_all_wifi() {
    clear_screen();
    banner();

    set_color(14);
    printf("  +------------------------------------------+\n");
    printf("  |        ALL SAVED WiFi + PASSWORDS        |\n");
    printf("  +------------------------------------------+\n\n");

    for (int i = 0; i < profile_count; i++) {
        set_color(11);
        printf("  [%02d] [WiFi] %-30s", i + 1, profiles[i]);
        show_password(profiles[i]);
    }

    set_color(14);
    printf("\n  ------------------------------------------\n");
    set_color(7);
    printf("  Total: %d networks found\n\n", profile_count);
}

void show_wifi_list() {
    set_color(14);
    printf("  +------------------------------------------+\n");
    printf("  |          SAVED WiFi NETWORKS             |\n");
    printf("  +------------------------------------------+\n\n");

    for (int i = 0; i < profile_count; i++) {
        set_color(11);
        printf("    [%02d] ", i + 1);
        set_color(15);
        printf("[WiFi] %s\n", profiles[i]);
    }

    set_color(14);
    printf("\n  ------------------------------------------\n");
    set_color(10);
    printf("  [00] Show ALL passwords at once\n");
    set_color(7);
    printf("\n");
}

void menu_select() {
    int choice;

    show_wifi_list();

    set_color(14);
    printf("  Enter network number: ");
    set_color(15);
    scanf("%d", &choice);
    printf("\n");

    if (choice == 0) {
        show_all_wifi();
    } else if (choice >= 1 && choice <= profile_count) {
        set_color(14);
        printf("  +------------------------------------------+\n");
        printf("  |                  RESULT                  |\n");
        printf("  +------------------------------------------+\n\n");

        set_color(11);
        printf("  [WiFi]    : ");
        set_color(15);
        printf("%s\n", profiles[choice - 1]);
        show_password(profiles[choice - 1]);
        printf("\n");
    } else {
        set_color(12);
        printf("  [X] Invalid choice!\n\n");
    }
}

int main() {
  
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    clear_screen();
    banner();

    load_profiles();

    set_color(14);
    printf("  +------------------------------------------+\n");
    printf("  |               MAIN MENU                  |\n");
    printf("  +------------------------------------------+\n\n");

    set_color(10);
    printf("    [1] ");
    set_color(15);
    printf("Start - View WiFi Passwords\n\n");

    set_color(12);
    printf("    [0] ");
    set_color(15);
    printf("Exit\n\n");

    set_color(14);
    printf("  ------------------------------------------\n");
    printf("  Your choice: ");
    set_color(15);

    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        clear_screen();
        banner();
        menu_select();
    } else {
        set_color(12);
        printf("\n  Goodbye!\n\n");
    }

    set_color(7);
    printf("  Press Enter to exit...");
    getchar();
    getchar();
    return 0;
}