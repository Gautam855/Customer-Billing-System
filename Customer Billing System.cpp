#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include <windows.h> // Include the Windows header file for gotoxy function

// Function to set the cursor position
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
struct Item {
    const char* name;
    float price;
    float quantity;
    float total;
};

void printMenu() {
    printf("\t\t\t\t================*******Menu*******================\n");
    printf("\t\t\t\t\t  Sno.  Item               Price\n");
    printf("\t\t\t\t--------------------------------------------------\n");
    printf("\t\t\t\t\t  1.    Pizza                60\n\t\t\t\t\t  2.    Pasta                90\n\t\t\t\t\t  3.    Momos                50\n\t\t\t\t\t  4.    Chowmin              40\n\t\t\t\t\t  5.    Maggie               60\n");
    printf("\t\t\t\t--------------------------------------------------\n");
    printf("\n\t\t\t\t\tPress Enter for Order");
    getchar();
    system("cls");
}

void printMenuInstructions() {
    printf("\t\t\t\t================*******Menu Instruction*******================\n");
    printf("\t\t\t\t\t\tPress Enter 0 For Exit.\n\t\t\t\t\t\tPress Enter 1 for Pizza.\n\t\t\t\t\t\tPress Enter 2 for Pasta.\n\t\t\t\t\t\tPress Enter 3 for Momos.\n\t\t\t\t\t\tPress Enter 4 for Chowmin.\n\t\t\t\t\t\tPress Enter 5 for Maggie.\n");
}

void printHeader() {
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
    printf("\n\n\t\t\tGautam Ka Dhaba\t\t\n \t\t     Mandawali Buddha Marg\n \t\t      Gali no.-2 1st Floor\n \t\t        Delhi - 110092\n \t\t       Tel: 8860022098\n \t\t       GSTIN : 209393921");
    printf("\n=================================================================");
    printf("\nBill no. \t\t T no. \t\t Date \t\t Time");
    printf("\n=================================================================");
    printf("\n2145\t\t \t D31   \t    %d-%02d-%02d \t\t %02d:%02d:%02d\n",tm.tm_mday, tm.tm_mon + 1,tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
printf("\n=================================================================");
}

void printItemRow(const char* item, float price, float quantity, float total) {
    // Align the columns using gotoxy function
    gotoxy(0, 3);
    printf("%s", item);
    gotoxy(26, 3);
    printf("%.2f", price);
    gotoxy(44, 3);
    printf("%.2f", quantity);
    gotoxy(60, 3);
    printf("%.2f", total);
}

void printSummary(float quantity, float grossTotal, float cgst, float discount, float grandTotal) {
    printf("\n=================================================================");
    printf("\nTotal Quantity \t\t\t\t%.2f", quantity);
    printf("\nGross Total \t\t\t\t\t\t%.2f", grossTotal);
    printf("\nCGST \t\t\t\t\t\t\t%.2f", cgst);
    printf("\nSGST \t\t\t\t\t\t\t%.2f", cgst);
    printf("\nDiscount \t\t\t\t\t\t%.2f", discount);
    printf("\n=================================================================\n");
    printf("\nGrand Total \t\t\t\t\t\t%.2f", grandTotal);
    printf("\n=================================================================\n");
}


float calculateGST(float amount) {
    return (amount * 18) / 100;
}

float calculateDiscount(float amount) {
    if (amount > 500 && amount < 750) {
        return (amount * 2.5) / 100;
    } else if (amount > 750 && amount < 1000) {
        return (amount * 5) / 100;
    } else if (amount > 1000 && amount < 1500) {
        return (amount * 7.5) / 100;
    } else if (amount > 1500) {
        return (amount * 10) / 100;
    } else {
        return 0.0;
    }
}

int main() {
    int choice;
    float total = 0, price, quantity, cgst, discount, grandTotal;
    Item items[5];
    int itemCount = 0;

    printMenu();
    printMenuInstructions();
    

    do {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        if (choice < 1 || choice > 5) {
            printf("please enter valid choice:\n");
            continue;
        }

        printf("Enter the quantity: ");
        scanf("%f", &quantity);
        getchar();

        Item* currentItem = NULL;

        // Check if the item is already ordered
        for (int i = 0; i < itemCount; i++) {
            if (strcmp(items[i].name, choice == 1 ? "Pizza" : choice == 2 ? "Pasta" : choice == 3 ? "Momos" : choice == 4 ? "Chowmin" : "Maggie") == 0) {
                currentItem = &items[i];
                break;
            }
        }

        

        switch (choice) {
            case 1:
                price = 60;
                break;
            case 2:
                price = 90;
                break;
            case 3:
                price = 50;
                break;
            case 4:
                price = 40;
                break;
            case 5:
                price = 60;
                break;
                
            default: printf("Please enter valid number");	
            			break;
        }
        if (currentItem != NULL) {
            // Item already exists, update the quantity and total
            currentItem->quantity += quantity;
            currentItem->price=price;
            currentItem->total += currentItem->price * quantity;
        } else {
            // Item doesn't exist, create a new item
            Item item;
            item.name = choice == 1 ? "Pizza" : choice == 2 ? "Pasta" : choice == 3 ? "Momos" : choice == 4 ? "Chowmin" : "Maggie";
            item.price = price;
            item.quantity = quantity;
            item.total = price * quantity;

            items[itemCount++] = item;
        }
				
        total += price * quantity;

        
    } while (choice != 0);

    cgst = calculateGST(total);
    discount = calculateDiscount(total);
    grandTotal = total + (2 * cgst) - discount;

	system("cls");
   
	printHeader();
	 printf("\n\nItem\t\t\tPrice\t\tQuantity\tTotal\n");
    printf("-------------------------------------------------------------\n");
quantity=0;
    for (int i = 0; i < itemCount; i++) {
        printf("%s\t\t\t%.2f\t\t%.2f\t\t%.2f\n", items[i].name, items[i].price, items[i].quantity, items[i].total);
		quantity+=  items[i].quantity;
    }
    printSummary(quantity, total, cgst, discount, grandTotal);
    return 0;
}

