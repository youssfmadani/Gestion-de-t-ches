#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define MAX_TASKS 30

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    char title[100];
    char description[256];
    Date due_date;
    char priority[10];
    int status;
} Task;

Task tasks[MAX_TASKS];
int task_count = 0;

void display_menu() {
     printf("\n----------------- Menu ----------------\n");
    printf("1. Ajouter une t�che\n");
    printf("2. Afficher les t�ches\n");
    printf("3. Modifier une t�che\n");
    printf("4. Supprimer une t�che\n");
    printf("5. Filtrer les t�ches\n");
    printf("6. Ordonner les t�ches par date\n");
    printf("7. Quitter et sauvegarder\n");
    printf("-----------------------------------------\n");
}

void add_task() {
    if (task_count >= MAX_TASKS) {
        printf("Limite de t�ches atteinte.\n");
        return;
    }
    Task new_task;
    printf("Titre : ");
    scanf(" %[^\n]", new_task.title);
    printf("Description : ");
    scanf(" %[^\n]", new_task.description);
    
    printf("Date d'�ch�ance (JJ MM AAAA) : ");
    scanf("%d %d %d", &new_task.due_date.day, &new_task.due_date.month, &new_task.due_date.year);
    
    printf("Priorit� (High/Low) : ");
    scanf("%s", new_task.priority);
    new_task.status = 0; // Incompl�te
    tasks[task_count++] = new_task;
    printf("T�che ajout�e avec succ�s.\n");
}

void display_tasks() {
    if (task_count == 0) {
        printf("Aucune t�che enregistr�e.\n");
        return;
    }
    printf("\nListe des t�ches :\n");
   int i=0;
    while(i < task_count) {
        printf("T�che %d:\n", i + 1);
        printf("Titre: %s\n", tasks[i].title);
        printf("Description: %s\n", tasks[i].description);
        printf("Date d'�ch�ance: %02d/%02d/%04d\n", tasks[i].due_date.day, tasks[i].due_date.month, tasks[i].due_date.year);
        printf("Priorit�: %s\n", tasks[i].priority);
        printf("Statut: %s\n", tasks[i].status ? "Compl�te" : "Incompl�te");
        i++;
    }
}

void modify_task() {
    int index;
    display_tasks();
    printf("Choisissez le num�ro de la t�che � modifier : ");
    scanf("%d", &index);
    
    if (index < 1 || index > task_count) {
        printf("Index invalide.\n");
        return;
    }
    
   
    int choice;
    
    printf("\nVoulez-vous modifier tous les d�tails ? (1 pour Oui, 0 pour Non) : ");
    int edit_all;
    scanf("%d", &edit_all);

    if (edit_all) {
        printf("Nouveau titre : ");
        scanf(" %[^\n]", tasks[index - 1].title);
        printf("Nouvelle description : ");
        scanf(" %[^\n]", tasks[index - 1].description);
        printf("Nouvelle date d'�ch�ance (JJ MM AAAA) : ");
        scanf("%d %d %d", &tasks[index - 1].due_date.day, &tasks[index - 1].due_date.month, &tasks[index - 1].due_date.year);
        printf("Nouvelle priorit� (High/Low) : ");
        scanf("%s", tasks[index - 1].priority);
        printf("Statut (0 pour Incompl�te, 1 pour Compl�te) : ");
        scanf("%d", &tasks[index - 1].status);
        printf("Tous les d�tails ont �t� mis � jour.\n");
    } else {
        do {
            printf("\nModifier la t�che %d : %s\n", index, tasks[index - 1].title);
            printf("1. Modifier la description\n");
            printf("2. Modifier la date d'�ch�ance\n");
            printf("3. Modifier la priorit�\n");
            printf("4. Modifier le statut\n");
            printf("0. Retourner au menu principal\n");
            printf("Choisissez une option : ");
            scanf("%d", &choice);
            
            switch (choice) {
                case 1:
                    printf("Nouvelle description : ");
                    scanf(" %[^\n]", tasks[index - 1].description);
                    printf("Description mise � jour.\n");
                    break;
                case 2:
                    printf("Nouvelle date d'�ch�ance (JJ MM AAAA) : ");
                    scanf("%d %d %d", &tasks[index - 1].due_date.day, &tasks[index - 1].due_date.month, &tasks[index - 1].due_date.year);
                    printf("Date d'�ch�ance mise � jour.\n");
                    break;
                case 3:
                    printf("Nouvelle priorit� (High/Low) : ");
                    scanf("%s", &tasks[index - 1].priority);
                    printf("Priorit� mise � jour.\n");
                    break;
                case 4:
                    printf("Statut (0 pour Incompl�te, 1 pour Compl�te) : ");
                    scanf("%d", &tasks[index - 1].status);
                    printf("Statut mis � jour.\n");
                    break;
                case 0:
                    printf("Retour au menu principal.\n");
                    break;
                default:
                    printf("Option invalide.\n");
                    break;
            }
        } while (choice != 0);
    }
}

void delete_task() {
    int index;
    if (task_count == 0) {
        printf("Aucune t�che enregistr�e.\n");
        return;
    }
    display_tasks();
    printf("Choisissez le num�ro de la t�che � supprimer : ");
    scanf("%d", &index);
    if (index < 1 || index > task_count) {
        printf("Index invalide.\n");
        return;
    }
    for(int i = index - 1; i < task_count - 1; i++) {
        tasks[i] = tasks[i + 1];
    }
    task_count--;
    printf("T�che supprim�e.\n");
}

void filter_tasks_by_priority() {
    if (task_count == 0) {
        printf("Aucune t�che enregistr�e.\n");
        return;
    }
    char priority[10];
    printf("Entrez la priorit� (High/Low) : ");
    scanf("%s", priority);
    int found = 0;
    for (int i = 0; i < task_count; i++) {
        if (strcmp(tasks[i].priority, priority) == 0) {
            printf("T�che %d:\n", i + 1);
            printf("Titre: %s\n", tasks[i].title);
            found = 1;
        }
    }
    if (!found) {
        printf("Aucune t�che trouv�e avec cette priorit�.\n");
    }
}

void display_tasks_by_status() {
    int status;
    printf("Filtrer par statut : (0 pour Incompl�te, 1 pour Compl�te) : ");
    scanf("%d", &status);
    
    printf("\nListe des t�ches avec le statut choisi :\n");
    int found = 0;
    
    for (int i = 0; i < task_count; i++) {
        if (tasks[i].status == status) {
            printf("T�che %d : %s\n", i + 1, tasks[i].title);
            printf("Description : %s\n", tasks[i].description);
            printf("Date d'�ch�ance : %02d/%02d/%04d\n", tasks[i].due_date.day, tasks[i].due_date.month, tasks[i].due_date.year);
            printf("Priorit� : %s\n", tasks[i].priority);
            printf("Statut : %s\n", status == 0 ? "Incompl�te" : "Compl�te");
            printf("\n");
            found = 1;
        }
    }
    
    if (!found) {
        printf("Aucune t�che trouv�e avec le statut choisi.\n");
    }
}

void filter_tasks() {
    int choice;
    printf("Choisissez un mode de filtrage :\n");
    printf("1. Filtrer par Priorit�\n");
    printf("2. Filtrer par Statut\n");
    printf("0. Retourner au menu principal\n");
    printf("Votre choix : ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        filter_tasks_by_priority();
    } else if (choice == 2) {
        display_tasks_by_status();
    } else if (choice == 0) {
        printf("Retour au menu principal.\n");
    } else {
        printf("Option invalide.\n");
    }
}

void sort_tasks() {
    if (task_count <= 1) {
        printf("Pas assez de t�ches pour trier.\n");
        return;
    }

    for (int i = 0; i < task_count - 1; i++) {
        for (int j = 0; j < task_count - i - 1; j++) {
            // Compare due dates
            if (tasks[j].due_date.year > tasks[j + 1].due_date.year ||
                (tasks[j].due_date.year == tasks[j + 1].due_date.year && tasks[j].due_date.month > tasks[j + 1].due_date.month) ||
                (tasks[j].due_date.year == tasks[j + 1].due_date.year && tasks[j].due_date.month == tasks[j + 1].due_date.month && tasks[j].due_date.day > tasks[j + 1].due_date.day)) {
                // Swap tasks
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }

    printf("T�ches tri�es par date d'�ch�ance.\n");
}






int main() {
	int choice;
	 
    printf("\n Bienvenue dans l'application - Gestion des t�ches - \n");

    while (1) {
        display_menu();
        printf("Choisissez une option : ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: 
                add_task(); 
                break;
            case 2: 
                display_tasks(); 
                break;
            case 3: 
                modify_task(); 
                break;
            case 4: 
                delete_task(); 
                break;
            case 5: 
                filter_tasks();
                break;
            case 6: 
                sort_tasks(); 
                break;
            case 7: 
            	//save_tasks_to_file(filename); // Sauvegarder les t�ches avant de quitter
                printf("Au revoir!\n");
                return 0;
            default: 
                printf("Option invalide. Veuillez r�essayer.\n");
        }
    }
	
	
	
	
	 return 0;
}

