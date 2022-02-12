#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

struct Insertion
{
    int ID;
    char name[500];
    char category[500];
    char dateofarrival[500];
    char supplierName[500];
    char supplierCountry[500];
    int quantity;
};

struct Node
{
    struct Insertion data;
    struct Node *next;
};

void displayMenu();
int idSearch(int id);
void display();
int insert();
void delete ();
void displaySearchValue(char *value, int value2);
void displaySpecificSearch();
int boradSearch(char *name, char *category, char *dataOfArrival, int quantity, char *supplierName, char *supplierCountry);
int updateProducts(int updateValue);

struct Node *head = NULL;
struct Node *current = NULL;
struct Node *prev = NULL;

void *deletionThread()
{

    delete ();
    return NULL;
}

int main(int argc, char const *argv[])
{
    displayMenu();
    return 0;
}

void displayMenu()
{
    pthread_t thread_id[10];

    printf("\n\nThis is a program for market product entry\n");
    printf("=================================================\n");
    printf("\t\tOperations\n");
    printf("=================================================\n");

    int i = 0;
    int searchValue = 0;

    int operation = 0;
    int updateValue = 0;
    int result = 0;
    int id;
    char name[500];

    while (i == 0)
    {
        printf("1.\tInsert Products\n");
        printf("2.\tUpdate Products\n");
        printf("3.\tDelete Products\n");
        printf("4.\tRead Products Information\n");

        printf("=================================================\n");
        printf("\tTo Terminate the program enter 0\n");
        printf("=================================================\n");
        printf("Enter your operation number: ");
        scanf("%d", &operation);

        if (operation == 0)
        {
            break;
        }
        else if (operation == 1)
        {
            int items;
            int check;

            printf("=================================================\n");
            printf("\tHow many products you want to insert:\n");
            printf("=================================================\n");
            printf("Enter the number of items to add: ");
            scanf("%d", &items);

            for (int i = 0; i < items; i++)
            {
                check = insert();
                if (check == 1)
                {
                    printf("\n=================================================\n");
                    printf("\tError, ID already exists\n");
                    printf("=================================================\n");
                    break;
                }
            }
            display();

            printf("=================================================\n");
            printf("1.\t Back to Menu\n");
            printf("0.\t Terminate Program\n");
            printf("Enter Operation: ");
            scanf("%d", &operation);
            printf("=================================================\n");
            if (operation == 1)
            {
                continue;
            }
            else
            {
                break;
            }
        }
        else if (operation == 2)
        {

            printf("=================================================\n");
            printf("\tEnter the product ID you want to update:\n");
            printf("=================================================\n");
            printf("Enter Product ID: ");
            scanf("%d", &id);

            if (idSearch(id) == 1)
            {
                result = updateProducts(updateValue);
                if (result == 1)
                {
                    printf("=================================================\n");
                    printf("\tSuccessful Update of %s\n", current->data.name);
                    printf("=================================================\n");

                    display();
                    current == NULL;

                    printf("=================================================\n");
                    printf("1.\t Back to Menu\n");
                    printf("0.\t Terminate Program\n");
                    printf("Enter Operation: ");
                    scanf("%d", &operation);
                    printf("=================================================\n");
                    if (operation == 1)
                    {
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    printf("\tUnsuccessful Update of %s\n", head->data.name);

                    printf("=================================================\n");
                    printf("1.\t Back to Menu\n");
                    printf("0.\t Terminate Program\n");
                    printf("Enter Operation: ");
                    scanf("%d", &operation);
                    printf("=================================================\n");
                    if (operation == 1)
                    {
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                printf("Product Doesn't Exist\n");
                printf("=================================================\n");
            }
        }
        else if (operation == 3)
        {
            int i = 0;
            while (i >= 0)
            {

                printf("=================================================\n");
                printf("\tEnter the product ID you want to delete:\n");
                printf("=================================================\n");
                printf("Enter Product ID: ");
                scanf("%d", &id);

                if (idSearch(id) == 1)
                {

                    if (pthread_create(&thread_id[i], NULL, deletionThread, NULL))
                    {
                        printf("\n=================================================\n");
                        printf("\tError in creating thread\n");
                        printf("=================================================\n");
                        break;
                    }
                    printf("\n=================================================\n");
                    printf("\tSuccessful Deletion\n");
                    printf("=================================================\n");
                }
                else
                {
                    printf("\n=================================================\n");
                    printf("\tProduct Doesnt Exist\n");
                    printf("=================================================\n");
                    break;
                }

                int op;
                printf("=================================================\n");
                printf("\tDo you want to continue:\n");
                printf("1.\tContinue\n");
                printf("2.\t Exit\n");
                printf("=================================================\n");
                printf("Enter operation: ");
                scanf("%d", &op);

                if (op == 2)
                {
                    break;
                }
                else if (op == 1)
                {

                    i++;
                    current == NULL;
                    prev == NULL;
                }
            }

            for (int j = 0; j < i; j++)
            {
                if (pthread_join(thread_id[j], NULL))
                {
                    printf("\n=================================================\n");
                    printf("\tError in joining thread\n");
                    printf("=================================================\n");
                    break;
                }
            }

            display();
            current == NULL;
            prev == NULL;
            printf("=================================================\n");
            printf("1.\t Back to Menu\n");
            printf("0.\t Terminate Program\n");
            printf("Enter Operation: ");
            scanf("%d", &operation);
            printf("=================================================\n");
            if (operation == 1)
            {
                continue;
            }
            else
            {
                break;
            }
        }
        else if (operation == 4)
        {
            printf("=================================================\n");
            printf("\tWhat type of search do you want:\n");
            printf("=================================================\n");
            printf("1.\tBroad Search\n");
            printf("2.\tSpecific Search\n");
            printf("=================================================\n");
            printf("Enter Search Type: ");
            scanf("%d", &searchValue);

            if (searchValue == 2)
            {
                printf("=================================================\n");
                printf("\tEnter the product ID:\n");
                printf("=================================================\n");
                printf("Enter Product ID: ");
                scanf("%d", &id);

                if (idSearch(id) == 1)
                {
                    displaySpecificSearch();
                    current == NULL;
                    prev == NULL;

                    printf("=================================================\n");
                    printf("1.\t Back to Menu\n");
                    printf("0.\t Terminate Program\n");
                    printf("=================================================\n");
                    printf("Enter Operation: ");
                    scanf("%d", &operation);
                    printf("=================================================\n");
                    if (operation == 1)
                    {
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    printf("\n=================================================\n");
                    printf("\tProduct Doesnt Exist\n");
                    printf("=================================================\n");
                    printf("1.\t Back to Menu\n");
                    printf("0.\t Terminate Program\n");
                    printf("=================================================\n");
                    printf("Enter Operation: ");
                    scanf("%d", &operation);
                    printf("=================================================\n");
                }
            }
            else if (searchValue == 1)
            {
                char value[500];
                int value2;

                int boradSearchValue;
                int check;
                printf("\n=================================================\n");
                printf("\tSelect Values you want to search for");
                printf("\n=================================================\n");
                printf("1.\tAll Products\n");
                printf("2.\tProduct Name\n");
                printf("3.\tDate of Arrival\n");
                printf("4.\tProduct Category\n");
                printf("5.\tSupplier Name\n");
                printf("6.\tSupplier Country\n");
                printf("7.\tQuantity Available\n");
                printf("8.\tExit\n");
                printf("=================================================\n");
                printf("\tEnter Search value:\n");
                printf("=================================================\n");
                printf("Enter Search value: ");
                scanf("%d", &boradSearchValue);
                if (boradSearchValue == 1)
                {
                    display();
                    current == NULL;
                    prev == NULL;
                }
                else if (boradSearchValue == 2)
                {

                    printf("=================================================\n");
                    printf("\tEnter the Product Name:\n");
                    printf("=================================================\n");
                    printf("Enter Product Name: ");
                    scanf("%s", &value);
                    check = boradSearch(value, "", "", -1, "", "");
                    if (check == 1)
                    {
                        displaySearchValue(value, -1);
                        current == NULL;
                        prev == NULL;
                    }
                }
                else if (boradSearchValue == 3)
                {
                    printf("=================================================\n");
                    printf("\tEnter the Date of Arrival:\n");
                    printf("=================================================\n");
                    printf("Enter Date of Arrival: ");
                    scanf("%s", &value);
                    check = boradSearch("", "", value, -1, "", "");
                    if (check == 1)
                    {
                        displaySearchValue(value, -1);
                        current == NULL;
                        prev == NULL;
                    }
                }
                else if (boradSearchValue == 4)
                {
                    printf("=================================================\n");
                    printf("\tEnter the Product Category:\n");
                    printf("=================================================\n");
                    printf("Enter Product Category: ");
                    scanf("%s", &value);
                    check = boradSearch("", value, "", -1, "", "");
                    if (check == 1)
                    {
                        displaySearchValue(value, -1);
                        current == NULL;
                        prev == NULL;
                    }
                }
                else if (boradSearchValue == 5)
                {
                    printf("=================================================\n");
                    printf("\tEnter the Supplier Name:\n");
                    printf("=================================================\n");
                    printf("Enter Supplier Name: ");
                    scanf("%s", &value);
                    check = boradSearch("", "", "", -1, value, "");
                    if (check == 1)
                    {
                        displaySearchValue(value, -1);
                        current == NULL;
                        prev == NULL;
                    }
                }
                else if (boradSearchValue == 6)
                {
                    printf("=================================================\n");
                    printf("\tEnter the Supplier Country:\n");
                    printf("=================================================\n");
                    printf("Enter Supplier Country: ");
                    scanf("%s", &value);
                    check = boradSearch("", "", "", -1, "", value);
                    if (check == 1)
                    {
                        displaySearchValue(value, -1);
                        current == NULL;
                        prev == NULL;
                    }
                }
                else if (boradSearchValue == 7)
                {
                    printf("=================================================\n");
                    printf("\tEnter the Quantity Available:\n");
                    printf("=================================================\n");
                    printf("Enter Quantity Available: ");
                    scanf("%d", &value2);
                    check = boradSearch("", "", "", value2, "", "");
                    if (check == 1)
                    {
                        displaySearchValue("", value2);
                        current == NULL;
                        prev == NULL;
                    }
                }

                else if (boradSearchValue == 8)
                {
                    printf("=============================================\n");
                    continue;
                }

                else
                {
                    printf("\n=================================================\n");
                    printf("\tInvalid Input\n");
                    printf("=================================================\n");
                }

                printf("=================================================\n");
                printf("1.\t Back to Menu\n");
                printf("0.\t Terminate Program\n");
                printf("Enter Operation: ");
                scanf("%d", &operation);
                printf("=================================================\n");
                if (operation == 1)
                {
                    continue;
                }
                else
                {
                    break;
                }
            }
        }

        else
        {
            printf("\n=================================================\n");
            printf("\tInvalid Input\n");
            printf("=================================================\n");
        }
    }
}

int insert()
{
    // Allocate memory for new node;
    struct Node *link = (struct Node *)malloc(sizeof(struct Node));
    struct Node *ptr = head;

    printf("=================================================\n");
    printf("\tInsert the product information:\n");
    printf("=================================================\n");

    printf("Product ID: ");
    scanf("%d", &link->data.ID);
    printf("\n");

    printf("Product Name: ");
    scanf("%s", &link->data.name);
    printf("\n");

    printf("Date of Arrival: ");
    scanf("%s", &link->data.dateofarrival);
    printf("\n");

    printf("Product Category: ");
    scanf("%s", &link->data.category);
    printf("\n");

    printf("Supplier Name: ");
    scanf("%s", &link->data.supplierName);
    printf("\n");

    printf("Supplier Country: ");
    scanf("%s", &link->data.supplierCountry);
    printf("\n");

    printf("Quantity Available: ");
    scanf("%d", &link->data.quantity);
    printf("\n");
    link->next = NULL;

    // If head is empty, create new list
    if (head == NULL)
    {
        head = link;
        head->next = link;
        return 0;
    }

    current = head;
    // move to the end of the list
    while (current->next != head)
        current = current->next;

    if (ptr->data.ID == link->data.ID)
    {
        free(link);
        return 1;
    }

    while (ptr->next != head)
    {
        if (ptr->data.ID != link->data.ID)
        {
            break;
        }
        else
        {
            free(link);
            return 1;
        }
        ptr = ptr->next;
    }
    if (ptr->data.ID == link->data.ID)
    {
        free(link);
        return 1;
    }

    // Insert link at the end of the list
    current->next = link;

    // Link the last node back to head
    link->next = head;
    return 0;
}

void display()
{
    if (head == NULL)
    {
        printf("\n=================================================\n");
        printf("\tThere are no data in the system..\n");
        printf("=================================================\n");
        return;
    }

    struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
    ptr = head;
    //start from the beginning
    while (ptr->next != head)
    {
        printf("\n=================================================\n");
        printf("\tHere are the data for the %s\n", ptr->data.name);
        printf("=================================================\n");

        printf("Product ID: %d\n", ptr->data.ID);
        printf("Product Name: %s\n", ptr->data.name);
        printf("Date of Arrival: %s\n", ptr->data.dateofarrival);
        printf("Product Category: %s\n", ptr->data.category);
        printf("Supplier Name: %s\n", ptr->data.supplierName);
        printf("Supplier Country: %s\n", ptr->data.supplierCountry);
        printf("Quantity Available: %d\n", ptr->data.quantity);

        printf("=================================================\n");
        ptr = ptr->next;
    }

    printf("\n=================================================\n");
    printf("\tHere are the data for the %s\n", ptr->data.name);
    printf("=================================================\n");

    printf("Product ID: %d\n", ptr->data.ID);
    printf("Product Name: %s\n", ptr->data.name);
    printf("Date of Arrival: %s\n", ptr->data.dateofarrival);
    printf("Product Category: %s\n", ptr->data.category);
    printf("Supplier Name: %s\n", ptr->data.supplierName);
    printf("Supplier Country: %s\n", ptr->data.supplierCountry);
    printf("Quantity Available: %d\n", ptr->data.quantity);

    printf("=================================================\n");
}

int idSearch(int id)
{

    if (head == NULL)
    {
        printf("\n=================================================\n");
        printf("\tThere are no data in the system..\n");
        printf("=================================================\n");
        return 0;
    }

    current = head;

    if (current->data.ID == id)
    {

        return 1;
    }

    while (current->next != head)
    {
        if (current->data.ID == id)
        {

            return 1;
        }

        prev = current;
        current = current->next;
    }
    if (current->data.ID == id)
    {

        return 1;
    }

    return 0;
}

int boradSearch(char *name, char *category, char *dataOfArrival, int quantity, char *supplierName, char *supplierCountry)
{

    if (head == NULL)
    {
        printf("\n=================================================\n");
        printf("\tThere are no data in the system..\n");
        printf("=================================================\n");
        return 0;
    }

    current = head;

    if (strcmp(category, "") == 0 && strcmp(dataOfArrival, "") == 0 && quantity == -1 && strcmp(supplierCountry, "") == 0 && strcmp(supplierName, "") == 0)
    {
        //name
        if (strcmp(current->data.name, name) == 0)
        {

            return 1;
        }
        while (current->next != head)
        {
            if (strcmp(current->data.name, name) != 0)
            {
                return 1;
            }

            prev = current;
            current = current->next;
        }
        if (strcmp(current->data.name, name) == 0)
        {

            return 1;
        }
    }
    else if (strcmp(name, "") == 0 && strcmp(dataOfArrival, "") == 0 && quantity == -1 && strcmp(supplierCountry, "") == 0 && strcmp(supplierName, "") == 0)
    {
        //category
        if (strcmp(current->data.category, category) == 0)
        {

            return 1;
        }
        while (current->next != head)
        {
            if (strcmp(current->data.category, category) == 0)
            {

                return 1;
            }

            prev = current;
            current = current->next;
        }
        if (strcmp(current->data.name, name) == 0)
        {

            return 1;
        }
    }
    else if (strcmp(name, "") == 0 && strcmp(category, "") == 0 && quantity == -1 && strcmp(supplierCountry, "") == 0 && strcmp(supplierName, "") == 0)
    {
        //dateOfArrival
        if (strcmp(current->data.dateofarrival, dataOfArrival) == 0)
        {

            return 1;
        }
        while (current->next != head)
        {
            if (strcmp(current->data.dateofarrival, dataOfArrival) == 0)
            {

                return 1;
            }
            prev = current;

            current = current->next;
        }
        if (strcmp(current->data.name, name) == 0)
        {

            return 1;
        }
    }
    else if (strcmp(name, "") == 0 && strcmp(dataOfArrival, "") == 0 && strcmp(category, "") == 0 && strcmp(supplierCountry, "") == 0 && strcmp(supplierName, "") == 0)
    {
        //quantity
        if (current->data.quantity == quantity)
        {

            return 1;
        }
        while (current->next != head)
        {
            if (current->data.quantity == quantity)
            {

                return 1;
            }
            prev = current;

            current = current->next;
        }
        if (strcmp(current->data.name, name) == 0)
        {

            return 1;
        }
    }
    else if (strcmp(name, "") == 0 && strcmp(dataOfArrival, "") == 0 && quantity == -1 && strcmp(category, "") == 0 && strcmp(supplierName, "") == 0)
    {
        //suplierCountry
        if (strcmp(current->data.supplierCountry, supplierCountry) == 0)
        {

            return 1;
        }
        while (current->next != head)
        {
            if (strcmp(current->data.supplierCountry, supplierCountry) == 0)
            {

                return 1;
            }
            prev = current;

            current = current->next;
        }
        if (strcmp(current->data.name, name) == 0)
        {

            return 1;
        }
    }
    else if (strcmp(name, "") == 0 && strcmp(dataOfArrival, "") == 0 && quantity == -1 && strcmp(supplierCountry, "") == 0 && strcmp(category, "") == 0)
    {
        //suplierName
        if (strcmp(current->data.supplierName, supplierName) == 0)
        {

            return 1;
        }
        while (current != head)
        {
            if (strcmp(current->data.supplierName, supplierName) == 0)
            {

                return 1;
            }
            prev = current;

            current = current->next;
        }
        if (strcmp(current->data.name, name) == 0)
        {

            return 1;
        }
    }
    else
    {
        return 0;
    }

    return 0;
}

void displaySearchValue(char *value, int value2)
{
    if (head == NULL)
    {
        printf("\n=================================================\n");
        printf("\tThere are no data in the system..\n");
        printf("=================================================\n");
        return;
    }
    struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));

    ptr = current;

    //start from the beginning
    while (ptr->next != current)
    {
        if (strcmp(ptr->data.category, value) == 0 || strcmp(ptr->data.name, value) == 0 || strcmp(ptr->data.dateofarrival, value) == 0 || strcmp(ptr->data.supplierCountry, value) == 0 || strcmp(ptr->data.supplierName, value) == 0 || ptr->data.quantity == value2)
        {
            printf("\n=================================================\n");
            printf("\tHere are the data for the %s\n", ptr->data.name);
            printf("=================================================\n");

            printf("Product ID: %d\n", ptr->data.ID);
            printf("Product Name: %s\n", ptr->data.name);
            printf("Date of Arrival: %s\n", ptr->data.dateofarrival);
            printf("Product Category: %s\n", ptr->data.category);
            printf("Supplier Name: %s\n", ptr->data.supplierName);
            printf("Supplier Country: %s\n", ptr->data.supplierCountry);
            printf("Quantity Available: %d\n", ptr->data.quantity);

            printf("=================================================\n");
        }

        ptr = ptr->next;
    }
    if (strcmp(ptr->data.category, value) == 0 || strcmp(ptr->data.name, value) == 0 || strcmp(ptr->data.dateofarrival, value) == 0 || strcmp(ptr->data.supplierCountry, value) == 0 || strcmp(ptr->data.supplierName, value) == 0 || ptr->data.quantity == value2)
    {
        printf("\n=================================================\n");
        printf("\tHere are the data for the %s\n", ptr->data.name);
        printf("=================================================\n");

        printf("Product ID: %d\n", ptr->data.ID);
        printf("Product Name: %s\n", ptr->data.name);
        printf("Date of Arrival: %s\n", ptr->data.dateofarrival);
        printf("Product Category: %s\n", ptr->data.category);
        printf("Supplier Name: %s\n", ptr->data.supplierName);
        printf("Supplier Country: %s\n", ptr->data.supplierCountry);
        printf("Quantity Available: %d\n", ptr->data.quantity);

        printf("=================================================\n");
    }
}

void displaySpecificSearch()
{
    if (head == NULL)
    {
        printf("\n=================================================\n");
        printf("\tThere are no data in the system..\n");
        printf("=================================================\n");
        return;
    }

    struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));

    ptr = current;

    printf("\n=================================================\n");
    printf("\tHere are the data for the %s\n", ptr->data.name);
    printf("=================================================\n");

    printf("Product ID: %d\n", ptr->data.ID);
    printf("Product Name: %s\n", ptr->data.name);
    printf("Date of Arrival: %s\n", ptr->data.dateofarrival);
    printf("Product Category: %s\n", ptr->data.category);
    printf("Supplier Name: %s\n", ptr->data.supplierName);
    printf("Supplier Country: %s\n", ptr->data.supplierCountry);
    printf("Quantity Available: %d\n", ptr->data.quantity);

    printf("=================================================\n");
}

int updateProducts(int updateValue)

{
    printf("=================================================\n");
    printf("\tSelect which value you want to update for %s:\n", &current->data.name);
    printf("=================================================\n");
    printf("1.\tProduct Name: %s\n", current->data.name);
    printf("2.\tDate of Arrival: %s\n", current->data.dateofarrival);
    printf("3.\tProduct Category: %s\n", current->data.category);
    printf("4.\tSupplier Name: %s\n", current->data.supplierName);
    printf("5.\tSupplier Country: %s\n", current->data.supplierCountry);
    printf("6.\tQuantity Available: %d\n", current->data.quantity);
    printf("7.\tExit\n");
    printf("=================================================\n");
    printf("Enter Update Value: ");
    scanf("%d", &updateValue);

    if (updateValue == 1)
    {
        printf("Update Product Name: ");
        scanf("%s", &current->data.name);

        return 1;
    }
    else if (updateValue == 2)
    {
        printf("Update Date of Arrival: ");
        scanf("%s", &current->data.dateofarrival);

        return 1;
    }
    else if (updateValue == 3)
    {
        printf("Update Product Category: ");
        scanf("%s", &current->data.category);

        return 1;
    }
    else if (updateValue == 4)
    {
        printf("Update Supplier Name: ");
        scanf("%s", &current->data.supplierName);
        return 1;
    }
    else if (updateValue == 5)
    {
        printf("Update Supplier Country: ");
        scanf("%s", &current->data.supplierCountry);
        return 1;
    }
    else if (updateValue == 6)
    {
        printf("Update Quantity Available: ");
        scanf("%d", &current->data.quantity);
        return 1;
    }
    else if (updateValue == 7)
    {
        return 0;
    }
    else
    {
        return 0;
    }
}

void delete ()
{
    if (head != current || current->next != head)
    {

        if (current == head)
        {

            prev = head;
            while (prev->next != head)
                prev = prev->next;
            head = current->next;
            prev->next = head;
            free(current);
        }
        else
        {

            prev->next = current->next;
            printf("%d", prev->data.ID);

            free(current);
        }
    }
    else
    {

        current = head;

        if (current->next == head)
        {
            head = NULL;
            free(current);
        }
    }
}