#include <stdio.h>
#include <string.h>

int a, b;

int sum(int x, int y) {
    return x + y;
}

void larger_and_sum() {
    printf("1st number: ");
    scanf("%d", &a);

    printf("2nd number: ");
    scanf("%d", &b);

    printf("%d is the larger number.\n", a > b ? a : b);
    printf("%d + %d = %d\n", a, b, sum(a,b));
    printf("\n");
}


// pointers to functions, useful for callbacks
void message_printer(int times, void (*callback) (char *msg), char *user_msg) {
    for (int i = 0; i < times; i++) {
        callback(user_msg);
    }
}

void message_of_the_day(char *msg) {
    printf("Message of the day: %s \n", msg);
}

void special_message(char *msg) {
    printf("A special message for ya: %s \n", msg);
}


struct drum {
    char name[10];
    int diameter;
    char material[20];
};

// defining as: typedef struct movie {..., allows forward declaration
typedef struct {
    char director[30];
    short year;
    char genre[20];
} movie;

void my_structs() {
    struct drum snare = {"snare", 14, "brass"};
    printf("My %s %s is %d inches.\n", snare.material, snare.name, snare.diameter);

    // intialising struct defined with typedef doesn't require the struct keyword 
    movie alien;

    strcpy(alien.director, "Ridley Scott");
    strcpy(alien.genre, "horror");
    alien.year = 1979;

    printf("My favourite %s film is Alien by %s in %d.\n", alien.genre, alien.director, alien.year);
    printf("\n");
}


int main() {
    larger_and_sum();

    my_structs();

    message_printer(1, message_of_the_day, "Hello world!");
    message_printer(3, special_message, "Goodbye world!");

    return 0;
}

