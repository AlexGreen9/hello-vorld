#include <stdio.h>
//сложение
int add(int a, int b) {
return a+b;}
//вычитание
int subtract(int a, int b) {
return a-b;}
//умножение
int multiply(int a, int b) {
return a*b;}
//деление
int divide(int a, int b) {
return a/b;}
int main() {
char choice;
int num1, num2;
do {
printf("Выберите действие (+, -, *, /) или 'q' для выхода: ");
scanf(" %c", &choice);
if (choice == 'q') {
break;
}
printf("Введите два числа: ");
scanf("%d %d", &num1, &num2);
switch (choice) {
case '+': printf("%d + %d = %d\n", num1, num2, add(num1, num2)); break;
case '-': printf("%d - %d = %d\n", num1, num2, subtract(num1, num2)); break;
case '*': printf("%d * %d = %d\n", num1, num2, multiply(num1, num2)); break;
case '/': 
if (num2 != 0) {
printf("%d / %d = %d\n", num1, num2, divide(num1, num2));
} else {
printf("Ошибка: деление на ноль!\n");
}
break;
default: printf("Неправильный выбор действия!\n"); break;
}
} while (1);
return 0;
}
/*int (*select(int choice)) (int, int) {
switch(choice) {
case 1: return add;
case 2: return subtract;
case 3: return multiply;
case 4: return divide;
}
}
int main () {
int (*operation) (int, int);
operation = select(1);
int result = operation(6, 4);
printf("result: %d \n" , result);
}*/

