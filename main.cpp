#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <ctime>

void buffer_overflow() {
    char buf[16];
    std::printf("Enter your name: ");
    std::scanf("%s", buf);                 // CWE-120/242 overflow possible
    char dest[8];
    std::strcpy(dest, buf);                // CWE-120
    std::printf("Hello %s\n", dest);
}

void format_string() {
    char input[256];
    std::printf("Say something: ");
    std::scanf("%255s", input);
    std::printf(input);                    // CWE-134
    std::printf("\n");
}

void command_injection() {
    char cmd[512];
    std::printf("Command to run: ");
    std::scanf("%511s", cmd);
    std::system(cmd);                      // CWE-78
}

void double_free() {
    char* p = (char*)std::malloc(10);
    std::free(p);
    std::free(p);                          // CWE-415
}

void use_after_free() {
    char* q = (char*)std::malloc(10);
    std::free(q);
    q[0] = 'A';                            // CWE-416
}

void uninitialized_use() {
    int x;                                 // CWE-457
    if (std::rand() % 2) { x = 42; }
    std::printf("Value: %d\n", x);
}

void insecure_tmpfile() {
    const char* path = "/tmp/insecure_cpp.tmp";
    std::FILE* f = std::fopen(path, "w+"); // CWE-377
    if (f) { std::fputs("secret\n", f); std::fclose(f); }
    std::system((std::string("chmod 777 ") + path).c_str()); // CWE-732
}

void insecure_sprintf() {
    char small[8];
    const char* big = "AAAAAAAAAAAAAAAAAAAA";
    std::sprintf(small, "%s", big);        // CWE-786/120
    std::puts(small);
}

void token_with_rand() {
    // CWE-330: usage de rand() pour un token
    std::srand((unsigned)std::time(nullptr));
    int t = std::rand();
    std::printf("Token=%d\n", t);
}

void path_traversal_read() {
    char file[256];
    std::printf("File to read: ");
    std::scanf("%255s", file);
    std::ifstream in(file);                // CWE-22 (aucune validation)
    std::string line;
    while (std::getline(in, line)) std::cout << line << "\n";
}

void leak_memory() {
    char* p = new char[1024 * 1024];       // CWE-401: fuite mémoire (jamais libérée)
    std::strcpy(p, "leaking...");
}

int main() {
    // CWE-798: secrets en dur
    const char* USER = "admin";
    const char* PASS = "admin";

    std::printf("Choose: 1) overflow 2) fstr 3) cmd 4) dfree 5) uaf 6) uinit 7) tmp 8) sprintf 9) rand 10) read 11) leak\n");
    int choice; std::scanf("%d", &choice);
    switch (choice) {
        case 1: buffer_overflow();   break;
        case 2: format_string();     break;
        case 3: command_injection(); break;
        case 4: double_free();       break;
        case 5: use_after_free();    break;
        case 6: uninitialized_use(); break;
        case 7: insecure_tmpfile();  break;
        case 8: insecure_sprintf();  break;
        case 9: token_with_rand();   break;
        case 10: path_traversal_read(); break;
        case 11: leak_memory();      break;
        default: std::puts("bye");
    }
    return 0;
}
