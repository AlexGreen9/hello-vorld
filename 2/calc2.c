#include <stdio.h>
// Объявление указателя на функцию
typedef int (*operation)(int, int);
//operation является просто название для указателя на функцию, принимающую два целочисленных аргумента и возвращающую целочисленное значение.
// Сложение
int add(int a, int b) {
return a + b;
}
// Вычитание
int subtract(int a, int b) {
return a - b;
}
// Умножение
int multiply(int a, int b) {
return a * b;
}
// Деление
int divide(int a, int b) {
if (b != 0) {
return a / b;
} else {
printf("Ошибка: деление на ноль!\n");
return 0;
}
}
int main() {
char choice;
int num1, num2;
operation operations[] = {add, subtract, multiply, divide}; 
//мы создаем массив указателей на функции operation, который называется operations, и инициализируем его указателями на функции
char operators[] = {'+', '-', '*', '/'};
int numOperations = sizeof(operations) / sizeof(operations[0]);
//мы вычисляем количество элементов в массиве operations путем деления общего размера массива на размер его первого элемента. 
//Резултат деления sizeof(operations) на sizeof(operations[0]) даст нам общее количество элементов в массиве operations, так как размер каждого элемента массива одинаков, а размер массива равен общему размеру рассматриваемых элементов, деленному на размер одного элемента.
do {
printf("Выберите действие %c", operators[0]);
for (int i = 1; i < numOperations; i++) {
printf(", %c", operators[i]);
}
printf(" или 'q' для выхода: ");
scanf(" %c", &choice);
if (choice == 'q') {
break;
}
printf("Введите два числа: ");
scanf("%d %d", &num1, &num2);
int selectedOperation = -1;
for (int i = 0; i < numOperations; i++) {
if (choice == operators[i]) {
selectedOperation = i;
break;
}
}
if (selectedOperation != -1) {
printf("%d %c %d = %d\n", num1, operators[selectedOperation], num2, operations[selectedOperation](num1, num2));
 } else {
printf("Неправильный выбор действия!\n");
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
