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

int check_date(int day, int month, int year) {
        if (year < 2024) {
            return 0; // Invalid year
        }
        if (month < 1 || month > 12) {
            return 0; // Invalid month
        }
        // Days in each month
        int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        // Check for leap year
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            days_in_month[2] = 29; // February has 29 days in a leap year
        }
        if (day < 1 || day > days_in_month[month]) {
            return 0; // Invalid day for the given month
        }
        return 1; // Valid date
    }

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
    printf("7. Sauvegarder les t�ches\n");
    printf("8. Charger les t�ches\n");
    printf("9. Quitter\n");
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

    int day, month, year;
    int is_valid_date = 0;

    do {
        printf("Date d'�ch�ance (JJ MM AAAA) : ");
        scanf("%d %d %d", &day, &month, &year);

        is_valid_date = check_date(day, month, year);

        if (!is_valid_date) {
            printf("Date invalide. Veuillez r�essayer.\n");
        }

    } while (!is_valid_date);

    new_task.due_date.day = day;
    new_task.due_date.month = month;
    new_task.due_date.year = year;

    do {
        printf("Priorit� (High/Low) : ");
        scanf("%s", new_task.priority);
        if (strcmp(new_task.priority, "High") != 0 && strcmp(new_task.priority, "Low") != 0) {
            printf("Priorit� invalide. Veuillez entrer 'High' ou 'Low'.\n");
        }
    } while (strcmp(new_task.priority, "High") != 0 && strcmp(new_task.priority, "Low") != 0);
    
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
	    printf("Date d'�ch�ance : %02d/%02d/%04d\n", tasks[i].due_date.day, tasks[i].due_date.month, tasks[i].due_date.year);
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

void save_tasks_to_file() {
    char filename[100]; 
    printf("Entrez le nom du fichier o� sauvegarder les t�ches (ex: tasks.txt) : ");
    scanf("%s", filename);

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erreur: Impossible d'ouvrir le fichier %s pour sauvegarder les t�ches.\n", filename);
        return;
    }

    for (int i = 0; i < task_count; i++) {
        if (fprintf(file, "%s\n%s\n%d %d %d\n%s\n%d\n", tasks[i].title, tasks[i].description,
                    tasks[i].due_date.day, tasks[i].due_date.month, tasks[i].due_date.year,
                    tasks[i].priority, tasks[i].status) < 0) {
            printf("Erreur: Un probl�me est survenu lors de l'�criture des t�ches dans le fichier %s.\n", filename);
            fclose(file);
            return;
        }
    }

    fclose(file);
    printf("T�ches sauvegard�es avec succ�s dans le fichier %s.\n", filename);
}

void load_tasks_from_file() {
    char filename[100];  
    printf("Entrez le nom du fichier � charger (ex: tasks.txt) : ");
    scanf("%s", filename);

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erreur: Impossible d'ouvrir le fichier %s pour charger les t�ches.\n", filename);
        return;
    }

    task_count = 0;
    while (fscanf(file, " %[^\n]\n%[^\n]\n%d %d %d\n%s\n%d\n", tasks[task_count].title,
                  tasks[task_count].description, &tasks[task_count].due_date.day,
                  &tasks[task_count].due_date.month, &tasks[task_count].due_date.year,
                  tasks[task_count].priority, &tasks[task_count].status) == 7) {
        task_count++;
        if (task_count >= MAX_TASKS) {
            printf("Erreur: Nombre maximal de t�ches atteint. Toutes les t�ches ne peuvent pas �tre charg�es.\n");
            break;
        }
    }

    fclose(file);
    printf("T�ches charg�es avec succ�s depuis le fichier %s.\n", filename);
}






int main() {
	int choice;
	char filename[] = "tasks.txt"; 
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
            	save_tasks_to_file(); // Sauvegarder les t�ches avant de quitter
            	break;
            case 8 :
            	load_tasks_from_file();
            	break;
            case 9 :
            	 printf("Au revoir!\n");
                return 0;
            default: 
                printf("Option invalide. Veuillez r�essayer.\n");
        }
    }
	
	
	
	
	 return 0;
}

