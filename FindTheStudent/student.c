#include "student.h"
#include "winsock.h"
#include <MYSQL/mysql.h>
#include <time.h>
#include <string.h>
#include "zerofgets.h"
#include <stdio.h>
#include <stdlib.h>
Student createStudent(){
    Student s;
    char * lastName  = malloc(sizeof(char)*130);
    char * firstName = malloc(sizeof(char)*130);
    char * promotion = malloc(sizeof(char)*30);

    printf("Nom de famille :");
    zerofgets(lastName,130);
    printf("\nPrenom :");
    zerofgets(firstName,130);
    printf("\nPromotion :");
    zerofgets(promotion,130);
    printf("\n");


    time_t t1  = time(NULL);
    s.id = t1;
    s.lastName = lastName;
    s.firstName = firstName;
    s.promotion = promotion;


    return s;
}

void removeStudent()
{
    Student s;

    printf("Veuillez saisir le num�ro INE : ");
    zerofgets(s.id, 130);
    printf("\n");
}

void searchStudent(){
    MYSQL mysql;
    mysql_init(&mysql);
    mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");
    if(mysql_real_connect(&mysql,"localhost","root","","student",0,NULL,0))
    {

        mysql_query(&mysql, "SELECT * FROM students");

        //D�claration des objets
        MYSQL_RES *result = NULL;
        MYSQL_ROW row;

        unsigned int i = 0;
        unsigned int num_champs = 0;

        //On met le jeu de r�sultat dans le pointeur result
        result = mysql_use_result(&mysql);

        //On r�cup�re le nombre de champs
        num_champs = mysql_num_fields(result);

        //Tant qu'il y a encore un r�sultat ...
        while ((row = mysql_fetch_row(result)))
        {
            //On d�clare un pointeur long non sign� pour y stocker la taille des valeurs
            unsigned long *lengths;

            //On stocke ces tailles dans le pointeur
            lengths = mysql_fetch_lengths(result);

            //On fait une boucle pour avoir la valeur de chaque champs
            for(i = 0; i < num_champs; i++)
            {
               //On ecrit toutes les valeurs
               printf("[%.*s] ", (int) lengths[i], row[i] ? row[i] : "NULL");
            }
            printf("\n");
        }

        //Lib�ration du jeu de r�sultat
        mysql_free_result(result);

        //Fermeture de MySQL
        mysql_close(&mysql);
    }

    else
    {
        printf("Une erreur s'est produite lors de la connexion � la BDD! (Avez vous pensez a allumer wamp)");
    }

}

void addStudent(Student stud) {
    MYSQL mysql;
    mysql_init(&mysql);
    mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");

    if(mysql_real_connect(&mysql,"localhost","root","","student",0,NULL,0))
    {

        char requete[250] = "";

        sprintf(requete, "INSERT INTO students VALUES('%d', '%s', '%s','%s')",stud.id,stud.lastName,stud.firstName,stud.promotion );
        mysql_query(&mysql, requete);
        mysql_close(&mysql);
    }
    else
    {
        printf("Une erreur s'est produite lors de la connexion � la BDD! (Avez vous pensez a allumer wamp)");
    }

}


void deleteStudent()
{
    char supr;
    MYSQL mysql;
    mysql_init(&mysql);
    mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");

    // R�cup�ration de la saisis utilisateur
    long etu;
    printf("Veuillez renseigner un num�ro INE  : ");
    scanf("%ld", &etu);
    // Condition MYSQL
     printf("�tes vous s�r (O/o Oui ! N/n Non)?\n");
                scanf("%c",&supr);
                if (supr == 'O' || supr == 'o'){
                    if(mysql_real_connect(&mysql,"localhost","root","","student",0,NULL,0)){
                        char requete[250] = "";
                        // REQUETE QUI SUPPRIME UN ETUDIANT EN FONCTION DE L'ID
                        sprintf(requete, "DELETE FROM students WHERE id = %d", etu);
                        mysql_query(&mysql, requete);
                        puts("ok");
                        mysql_close(&mysql);
                    }
                    else{
                        printf("Une erreur s'est produite lors de la connexion � la BDD!");
                    }
                }else{
                    printf("Aucune actions faite!");
                }


}

void updateStudent()
{

    MYSQL mysql;
    mysql_init(&mysql);
    mysql_options(&mysql,MYSQL_READ_DEFAULT_GROUP,"option");

    // R�cup�ration de l'ID d'un �l�ve pour l'update
    long etu;
    printf("Veuillez renseigner un num�ro INE  : ");
    scanf("%ld", &etu);

    // R�cup�ration de nouvelles variables
    char newlastname;
    char newfirstname;
    char newpromotion;

    //Saisis des nouvelles valeurs par l'utilisateur
    printf("Saisir un nouveau nom pour cette �tudiant :\n");
    scanf("%s", &newlastname);
    printf("Saisir un nouveau pr�nom  pour cette �tudiant: \n");
    scanf("%s", &newfirstname);
    printf("Saisir une nouvelle classe pour cette �tudiant : \n");
    scanf("%s", &newpromotion);

    if(mysql_real_connect(&mysql,"localhost","root","","student",0,NULL,0))
    {

        char requete[250] = "";
        // REQUETE SQL QUI MODIFIE UN ETUDIANT EN FONCTION DE SON NUMERO INE
        sprintf(requete, "UPDATE students SET lastName = '%s' firstName = '%s', promotion = '%s' WHERE id = %d", newlastname, newfirstname, newpromotion, etu);
        mysql_query(&mysql, requete);
        puts("ok");
        mysql_close(&mysql);
    }
    else
    {
        printf("Hum on doit �ter con !");
    }

}





