#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int id;
    char name[30];
    char status[10];          
    struct Node *prev, *next; 
} Node;

Node* head = NULL;

Node* createNode(int id, char name[]) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->id = id;
    strcpy(newNode->name, name);
    strcpy(newNode->status, "Absent");
    newNode->prev = newNode->next = NULL;
    return newNode;
}

int idExists(int id) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->id == id)
            return 1;   
        temp = temp->next;
    }
    return 0; 
}

void addEmployee(int id, char name[]) {

    if (idExists(id)) {
        printf("Error: Employee ID already exists. Use a unique ID.\n");
        return;
    }

    Node* newNode = createNode(id, name);

    if (head == NULL) {
        head = newNode;
        printf("Employee added.\n");
        return;
    }

    Node* temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
    newNode->prev = temp;

    printf("Employee added.\n");
}


void deleteEmployee(int id) {
    Node* temp = head;

    while (temp != NULL && temp->id != id)
        temp = temp->next;

    if (temp == NULL) {
        printf("Employee not found.\n");
        return;
    }

    if (temp->prev != NULL)
        temp->prev->next = temp->next;
    else
        head = temp->next;

    if (temp->next != NULL)
        temp->next->prev = temp->prev;

    free(temp);
    printf("Employee deleted.\n");
}

void markAttendance(int id, char status[]) {
    Node* temp = head;

    while (temp != NULL) {
        if (temp->id == id) {
            strcpy(temp->status, status);
            printf("Attendance updated.\n");
            return;
        }
        temp = temp->next;
    }
    printf("Employee not found.\n");
}

void updateName(int id, char newname[]) {
    Node* temp = head;

    while (temp != NULL) {
        if (temp->id == id) {
            strcpy(temp->name, newname);
            printf("Employee name updated.\n");
            return;
        }
        temp = temp->next;
    }
    printf("Employee not found.\n");
}

void searchEmployee(int id) {
    Node* temp = head;

    while (temp != NULL) {
        if (temp->id == id) {
            printf("\nEmployee Found:\nID: %d\nName: %s\nStatus: %s\n",
                   temp->id, temp->name, temp->status);
            return;
        }
        temp = temp->next;
    }
    printf("Employee not found.\n");
}

void display() {
    Node* temp = head;
    
    if (temp == NULL) {
        printf("No employees in the list.\n");
        return;
    }

    printf("\nEmployee Attendance List:\n");
    printf("--------------------------------------\n");

    while (temp != NULL) {
        printf("ID: %d | Name: %-10s | Status: %s\n",
               temp->id, temp->name, temp->status);
        temp = temp->next;
    }
}

void attendanceSummary() {
    int present = 0, absent = 0;
    Node* temp = head;

    while (temp != NULL) {
        if (!strcmp(temp->status, "Present"))
            present++;
        else
            absent++;
        temp = temp->next;
    }

    printf("\nAttendance Summary:\n");
    printf("------------------------\n");
    printf("Present: %d\n", present);
    printf("Absent : %d\n", absent);
}

int main() {
    int choice, id;
    char name[30];

    while (1) {
        printf("\n===== Employee Attendance System =====\n");
        printf("1. Add Employee\n");
        printf("2. Delete Employee\n");
        printf("3. Mark Present\n");
        printf("4. Mark Absent\n");
        printf("5. Update Employee Name\n");
        printf("6. Search Employee\n");
        printf("7. Display All Employees\n");
        printf("8. Attendance Summary\n");
        printf("9. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter ID: ");
                scanf("%d", &id);
                printf("Enter Name: ");
                scanf("%s", name);
                addEmployee(id, name);
                break;

            case 2:
                printf("Enter ID: ");
                scanf("%d", &id);
                deleteEmployee(id);
                break;

            case 3:
                printf("Enter ID: ");
                scanf("%d", &id);
                markAttendance(id, "Present");
                break;

            case 4:
                printf("Enter ID: ");
                scanf("%d", &id);
                markAttendance(id, "Absent");
                break;

            case 5:
                printf("Enter ID: ");
                scanf("%d", &id);
                printf("Enter New Name: ");
                scanf("%s", name);
                updateName(id, name);
                break;

            case 6:
                printf("Enter ID: ");
                scanf("%d", &id);
                searchEmployee(id);
                break;

            case 7:
                display();
                break;

            case 8:
                attendanceSummary();
                break;

            case 9:
                exit(0);

            default:
                printf("Invalid choice.\n");
        }
    }
}
