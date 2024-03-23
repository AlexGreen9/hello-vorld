#ifndef PERSON_H
#define PERSON_H
struct Contact {
char empty_string[1]; 
    char last_name[50];
    char first_name[50];
    char phone_numbers[20]; //  max 20 characters each
    struct Soc soci;
    struct Work wor;
};
#endif
