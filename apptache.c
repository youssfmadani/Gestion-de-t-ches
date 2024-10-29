#include <stdio.h>
#include <stdlib.h>

#define MAX 30

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



void display_menu() {
     printf("\n----------------- Menu -----------------\n");
    printf("1. Ajouter une tâche\n");
    printf("2. Afficher les tâches\n");
    printf("3. Modifier une tâche\n");
    printf("4. Supprimer une tâche\n");
    printf("5. Filtrer les tâches\n");
    printf("6. Ordonner les tâches par date\n");
    printf("7. Quitter et sauvegarder\n");
    printf("-----------------------------------------\n");
}

void add_task() {
    if (task_count >= MAX_TASKS) {
        printf("Limite de tâches atteinte.\n");
        return;
    }
    Task new_task;
    printf("Titre : ");
    scanf(" %[^\n]", new_task.title);
    printf("Description : ");
    scanf(" %[^\n]", new_task.description);
    
    printf("Date d'échéance (JJ MM AAAA) : ");
    scanf("%d %d %d", &new_task.due_date.day, &new_task.due_date.month, &new_task.due_date.year);
    
    printf("Priorité (High/Low) : ");
    scanf("%s", new_task.priority);
    new_task.status = 0; // Incomplète
    tasks[task_count++] = new_task;
    printf("Tâche ajoutée avec succès.\n");
}

void display_tasks() {
    if (task_count == 0) {
        printf("Aucune tâche enregistrée.\n");
        return;
    }
    printf("\nListe des tâches :\n");
    for (int i = 0; i < task_count; i++) {
        printf("Tâche %d:\n", i + 1);
        printf("Titre: %s\n", tasks[i].title);
        printf("Description: %s\n", tasks[i].description);
        printf("Date d'échéance: %02d/%02d/%04d\n", tasks[i].due_date.day, tasks[i].due_date.month, tasks[i].due_date.year);
        printf("Priorité: %s\n", tasks[i].priority);
        printf("Statut: %s\n", tasks[i].status ? "Complète" : "Incomplète");
    }
}

void modify_task() {
    int index;
    display_tasks();
    printf("Choisissez le numéro de la tâche à modifier : ");
    scanf("%d", &index);
    
    if (index < 1 || index > task_count) {
        printf("Index invalide.\n");
        return;
    }
    
   
    int choice;
    
    printf("\nVoulez-vous modifier tous les détails ? (1 pour Oui, 0 pour Non) : ");
    int edit_all;
    scanf("%d", &edit_all);

    if (edit_all) {
        printf("Nouveau titre : ");
        scanf(" %[^\n]", tasks[index - 1].title);
        printf("Nouvelle description : ");
        scanf(" %[^\n]", tasks[index - 1].description);
        printf("Nouvelle date d'échéance (JJ MM AAAA) : ");
        scanf("%d %d %d", &tasks[index - 1].due_date.day, &tasks[index - 1].due_date.month, &tasks[index - 1].due_date.year);
        printf("Nouvelle priorité (High/Low) : ");
        scanf("%s", tasks[index - 1].priority);
        printf("Statut (0 pour Incomplète, 1 pour Complète) : ");
        scanf("%d", &tasks[index - 1].status);
        printf("Tous les détails ont été mis à jour.\n");
    } else {
        do {
            printf("\nModifier la tâche %d : %s\n", index, tasks[index - 1].title);
            printf("1. Modifier la description\n");
            printf("2. Modifier la date d'échéance\n");
            printf("3. Modifier la priorité\n");
            printf("4. Modifier le statut\n");
            printf("0. Retourner au menu principal\n");
            printf("Choisissez une option : ");
            scanf("%d", &choice);
            
            switch (choice) {
                case 1:
                    printf("Nouvelle description : ");
                    scanf(" %[^\n]", tasks[index - 1].description);
                    printf("Description mise à jour.\n");
                    break;
                case 2:
                    printf("Nouvelle date d'échéance (JJ MM AAAA) : ");
                    scanf("%d %d %d", &tasks[index - 1].due_date.day, &tasks[index - 1].due_date.month, &tasks[index - 1].due_date.year);
                    printf("Date d'échéance mise à jour.\n");
                    break;
                case 3:
                    printf("Nouvelle priorité (High/Low) : ");
                    scanf("%s", &tasks[index - 1].priority);
                    printf("Priorité mise à jour.\n");
                    break;
                case 4:
                    printf("Statut (0 pour Incomplète, 1 pour Complète) : ");
                    scanf("%d", &tasks[index - 1].status);
                    printf("Statut mis à jour.\n");
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



Task tasks[MAX_TASKS];
int task_count = 0;




int main() {
	
	
	
	
	
	 return 0;
}

