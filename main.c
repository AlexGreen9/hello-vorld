#include <stdio.h>
#include "copy.h"
#include "two.h"
#include "one.h"
#include "person.h"
int main() {
    int choice;
    while (1) {
        printf("\nChoose an option:\n");
        printf("1. Add contact\n");
        printf("2. Edit contact\n");
        printf("3. Delete contact\n");
        printf("4. List contacts\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                add_contact();
                break;
            case 2:
                edit_contact();
                break;
            case 3:
                delete_contact();
                break;
            case 4:
                list_contacts();
                break;
case 5:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
  //  return 0;
}
