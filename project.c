#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 30

struct emp_data {
    int empno;
    char empName[MAX];
    char designation[MAX];
    struct emp_data *next;
};

// Function to insert a node at the beginning of the linked list
struct emp_data *insertFirst(struct emp_data *plist, int id, char name[], char desg[]) {
    struct emp_data *temp = (struct emp_data*)malloc(sizeof(struct emp_data));

    if (temp == NULL) {
        printf("\n Allocation failed \n");
        exit(2);
    }

    temp->empno = id;
    strcpy(temp->empName, name);
    strcpy(temp->designation, desg);
    temp->next = plist;
    plist = temp;
    return plist;
}

// Function to insert a node at the end of the linked list
struct emp_data *insertLast(struct emp_data *plist, int id, char name[], char desg[]) {
    struct emp_data *temp = (struct emp_data*)malloc(sizeof(struct emp_data));
    struct emp_data *ptr;

    if (temp == NULL) {
        printf("\n Allocation failed \n");
        exit(2);
    }

    temp->empno = id;
    strcpy(temp->empName, name);
    strcpy(temp->designation, desg);
    temp->next = NULL;

    if (plist == NULL) {
        return temp;
    }

    for (ptr = plist; ptr->next != NULL; ptr = ptr->next);
    ptr->next = temp;

    return plist;
}

// Function to insert a node after a specific employee number
struct emp_data *insertAfter(struct emp_data *plist, int id, char name[], char desg[], int afterId) {
    struct emp_data *temp = (struct emp_data*)malloc(sizeof(struct emp_data));
    struct emp_data *ptr = plist;

    if (temp == NULL) {
        printf("\n Allocation failed \n");
        exit(2);
    }

    while (ptr != NULL && ptr->empno != afterId) {
        ptr = ptr->next;
    }

    if (ptr == NULL) {
        printf("\n Employee Number %d not found for insertion \n", afterId);
        free(temp);
        return plist;
    }

    temp->empno = id;
    strcpy(temp->empName, name);
    strcpy(temp->designation, desg);
    temp->next = ptr->next;
    ptr->next = temp;

    return plist;
}

// Function to print the details of a node
void printNode(struct emp_data *p) {
    printf("\n Employee Details:\n");
    printf("\n Employee No    : %d", p->empno);
    printf("\n Name           : %s", p->empName);
    printf("\n Designation    : %s\n", p->designation);
    printf("-------------------------------------\n");
}

// Function to delete a node by employee number
struct emp_data* deleteNode(struct emp_data *plist, int id) {
    struct emp_data *ptr;
    struct emp_data *bptr;

    if (plist == NULL) {
        printf("\n List is empty.\n");
        return plist;
    }

    if (plist->empno == id) {
        ptr = plist;
        printf("\n Node deleted:");
        printNode(plist);
        plist = plist->next;
        free(ptr);
        return plist;
    }
    for (ptr = plist->next, bptr = plist; ptr != NULL; ptr = ptr->next, bptr = bptr->next) {
        if (ptr->empno == id) {
            printf("\n Node deleted:");
            printNode(ptr);
            bptr->next = ptr->next;
            free(ptr);
            return plist;
        }
    }
    printf("\n Employee Number %d not found ", id);
    return plist;
}

// Function to search for a node by employee number
void search(struct emp_data *plist, int key) {
    struct emp_data *ptr;

    for (ptr = plist; ptr != NULL; ptr = ptr->next) {
        if (ptr->empno == key) {
            printf("\n Key found:");
            printNode(ptr);
            return;
        }
    }
    printf("\n Employee Number %d not found ", key);
}

// Function to display all nodes
void display(struct emp_data *plist) {
    struct emp_data *ptr;

    for (ptr = plist; ptr != NULL; ptr = ptr->next) {
        printNode(ptr);
    }
}

// Function to sort the linked list in ascending order
struct emp_data* sortAsc(struct emp_data *plist) {
    struct emp_data *i, *j;
    int tempEmpNo;
    char tempEmpName[MAX], tempDesignation[MAX];

    for (i = plist; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->empno > j->empno) {
                tempEmpNo = i->empno;
                strcpy(tempEmpName, i->empName);
                strcpy(tempDesignation, i->designation);

                i->empno = j->empno;
                strcpy(i->empName, j->empName);
                strcpy(i->designation, j->designation);

                j->empno = tempEmpNo;
                strcpy(j->empName, tempEmpName);
                strcpy(j->designation, tempDesignation);
            }
        }
    }
    return plist;
}

// Function to sort the linked list in descending order
struct emp_data* sortDsc(struct emp_data *plist) {
    struct emp_data *i, *j;
    int tempEmpNo;
    char tempEmpName[MAX], tempDesignation[MAX];

    for (i = plist; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->empno < j->empno) {
                tempEmpNo = i->empno;
                strcpy(tempEmpName, i->empName);
                strcpy(tempDesignation, i->designation);

                i->empno = j->empno;
                strcpy(i->empName, j->empName);
                strcpy(i->designation, j->designation);

                j->empno = tempEmpNo;
                strcpy(j->empName, tempEmpName);
                strcpy(j->designation, tempDesignation);
            }
        }
    }
    return plist;
}

// Function to display the menu options
void menu() {
    printf("---------------------------------------------\n");
    printf("Enter option: \n");
    printf("1. to DISPLAY the records\n");
    printf("2. Count All Node\n");
    printf("3. to SEARCH the records\n");
    printf("4. to INSERT records into the database\n");
    printf("5. to SORT the records in ascending order\n");
    printf("6. to SORT the records in descending order\n");
    printf("7. to DELETE a record from the database\n");
    printf("8. to SAVE records to file\n");
    printf("9. to LOAD records from file\n");
    printf("10. to EXIT\n");
    printf("---------------------------------------------\n");
}

// Function to check if an employee number is duplicate
int isDuplicateEmpNo(struct emp_data *plist, int eno) {
    struct emp_data *ptr = plist;
    while (ptr != NULL) {
        if (ptr->empno == eno) {
            return 1;
        }
        ptr = ptr->next;
    }
    return 0;
}

// Function to get employee details from the user
void getEmployeeDetails(struct emp_data *plist, int *eno, char name[], char desig[]) {
    int valid = 0;
    while (!valid) {
        printf("\n Enter the Employee Number: ");
        if (scanf("%d", eno) != 1) {
            while (getchar() != '\n'); // Clear the input buffer
            printf("\n Invalid input. Please enter a number.\n");
            continue;
        }
        if (isDuplicateEmpNo(plist, *eno)) {
            printf("\n Employee Number already exists. Please enter a unique number.\n");
            continue;
        }
        valid = 1;
    }
    printf(" Enter the Employee name: ");
    getchar(); // Clear newline character left by scanf
    fgets(name, MAX, stdin);
    name[strcspn(name, "\n")] = 0; // Remove trailing newline character
    printf(" Enter the Employee Designation: ");
    fgets(desig, MAX, stdin);
    desig[strcspn(desig, "\n")] = 0; // Remove trailing newline character
}

// Function to insert initial employees into the linked list
void insertInitialEmployees(struct emp_data **plist) {
    int num, i, eno;
    char name[MAX], desig[MAX];

    printf("\n How many employees do you want to insert initially? ");
    scanf("%d", &num);

    for (i = 0; i < num; i++) {
        printf("\nEmployee %d\n", i + 1);
        getEmployeeDetails(*plist, &eno, name, desig);
        *plist = insertFirst(*plist, eno, name, desig);
    }
}

// Function to save the linked list to a file
void saveToFile(struct emp_data *plist) {
    FILE *file = fopen("employee_data.txt", "w");
    if (file == NULL) {
        printf("\n Error opening file for writing.\n");
        return;
    }

    struct emp_data *ptr = plist;
    while (ptr != NULL) {
        fprintf(file, "%d,%s,%s\n", ptr->empno, ptr->empName, ptr->designation);
        ptr = ptr->next;
    }

    fclose(file);
    printf("\n Data saved to file successfully.\n");
}

// Function to load the linked list from a file
struct emp_data* loadFromFile() {
    FILE *file = fopen("employee_data.txt", "r");
    if (file == NULL) {
        printf("\n Error opening file for reading.\n");
        return NULL;
    }

    struct emp_data *plist = NULL;
    int eno;
    char name[MAX], desig[MAX];

    while (fscanf(file, "%d,%29[^,],%29[^\n]\n", &eno, name, desig) == 3) {
        plist = insertLast(plist, eno, name, desig);
    }

    fclose(file);
    printf("\n Data loaded from file successfully.\n");
    return plist;
}

int main() {
    struct emp_data *plist = NULL;
    char name[MAX], desig[MAX];
    int choice;
    int eno;

    printf("\n Database is empty. Please enter the first records.\n");
    printf("---------------------------------------------\n");
    insertInitialEmployees(&plist);

    printf("\n\n Database created successfully.\n");
    display(plist);

    printf("\n MAIN MENU \n");

    while (1) {
        menu();
        printf("\n Enter choice : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (plist == NULL) {
                    printf("\n List is empty.");
                } else {
                    display(plist);
                }
                break;

            case 2: {
                int count = 0;
                struct emp_data *ptr;

                if (plist == NULL) {
                    printf("\n List is empty.");
                } else {
                    for (ptr = plist; ptr != NULL; ptr = ptr->next) {
                        count++;
                    }
                    printf("\n Total number of nodes: %d\n", count);
                }
                break;
            }

            case 3:
                printf("\n\n Enter the employee number to be searched: ");
                scanf("%d", &eno);
                search(plist, eno);
                break;

            case 4: {
                printf("\nSelect the position to insert the record:\n");
                printf("1 to INSERT a record at the beginning\n");
                printf("2 to INSERT a record at the end\n");
                printf("3 to INSERT a record after a specific employee number\n");
                int insertChoice;
                scanf("%d", &insertChoice);
                getEmployeeDetails(plist, &eno, name, desig);

                switch (insertChoice) {
                    case 1:
                        plist = insertFirst(plist, eno, name, desig);
                        break;
                    case 2:
                        plist = insertLast(plist, eno, name, desig);
                        break;
                    case 3:
                        printf("\n Enter the Employee Number after which to insert: ");
                        int afterId;
                        scanf("%d", &afterId);
                        plist = insertAfter(plist, eno, name, desig, afterId);
                        break;
                    default:
                        printf("Invalid option. Please try again.\n");
                }
                break;
            }

            case 5:
                plist = sortAsc(plist);
                printf("\n Records sorted in ascending order.\n");
                break;

            case 6:
                plist = sortDsc(plist);
                printf("\n Records sorted in descending order.\n");
                break;

            case 7:
                printf("\n\n Enter the employee number to be deleted: ");
                scanf("%d", &eno);
                plist = deleteNode(plist, eno);
                break;

            case 8:
                saveToFile(plist);
                break;

            case 9:
                plist = loadFromFile();
                break;

            case 10:
                exit(0);

            default:
                printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}
