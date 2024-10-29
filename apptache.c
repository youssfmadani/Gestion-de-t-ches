#include <stdio.h>
#include <stdlib.h>

#define MAX 30

typedef struct {
    char title[100];
    char description[256];
    Date due_date;
    char priority[10];
    int status;
} Task;

typedef struct {
    int day;
    int month;
    int year;
} Date;

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


Task tasks[MAX_TASKS];
int task_count = 0;




int main() {
	
	
	
	
	
	 return 0;
}

