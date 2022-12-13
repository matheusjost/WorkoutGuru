#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include <glib-2.0/glib/gstdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "tree.h" //MODULO COM A FUNÇÃO PARA INTEGRAÇÃO DOS RESULTADOS COM A ÁRVORE

int *answer;

/* Struct é definida para facilitar o manuseamento de janelas, builders e dados da aplicação */
typedef struct{
    GtkWindow *window;
    GtkBuilder *builder;
    GtkApplication *app;
}appdata;

/* Árvore a ser utilizada como parâmetro ao chamar o módulo tree.c */
tipo_no *first_tree;

/* HEADERS */
static GtkBuilder *get_builder_from_file(char *filename, GtkApplication *app);
static void main_app_screen(GtkApplication *app, gpointer user_data);
static void q1_screen(GtkWidget *widget, gpointer data);
static void handle_answer_d1(GtkWidget *widget, gpointer data);
static void handle_answer_d2(GtkWidget *widget, gpointer data);
static void handle_answer_d3(GtkWidget *widget, gpointer data);
static void handle_answer_d4(GtkWidget *widget, gpointer data);
static void handle_answer_d5(GtkWidget *widget, gpointer data);
static void handle_answer_d6(GtkWidget *widget, gpointer data);
static void handle_answer_objA(GtkWidget *widget, gpointer data);
static void handle_answer_objB(GtkWidget *widget, gpointer data);
static void save_file_screen1(GtkWidget *widget, gpointer data);
static void save_file_screen2(GtkWidget *widget, gpointer data);
static void export_file(GtkWidget *widget, gpointer data);
static void close_final(GtkWidget *widget, gpointer data);

void inicializa_arvore();
void insere_recursivo(tipo_no **p, int codigo, int treino, const char pergunta[100]);
void inserir_dados(tipo_no **p);
int gera_treino(tipo_no**p,int *respostas, int i);
const char* retorna_treino(tipo_no **p,int *respostas);
const char* carrega(tipo_no **p,int *respostas);
void in_ordem(tipo_no *ptAux);
void imprime_ARVORE( tipo_no *ptAux );

int main(int argc, char *argv[]){
    appdata *app_data = malloc(sizeof(appdata));

    /* Seta NULL nos ponteiros que instanciam as janelas, 
       o builder e o app para posteriormente rodar a interface */
    GtkApplication *app = gtk_application_new("ped.gracehopper.WorkoutGuru", G_APPLICATION_FLAGS_NONE);
    app_data->app = app;
    app_data->window = NULL;
    app_data->builder = NULL;


    /* Cria lista das respostas a serem enviadas para a função */
    answer = (int*) malloc(sizeof(int*));

    /* Conecta o sinal de abertura do app com a tela principal */
    g_signal_connect(app, "activate", G_CALLBACK(main_app_screen), app_data);

    /* Cria um int de status para retornar se a aplicação está rodando */
    int status = g_application_run(G_APPLICATION(app), argc, argv);

    /*
    TESTES
    printf("i1: %i\n", answer[0]);
    printf("i2: %i\n", answer[1]);
    printf("i3: %i\n", answer[2]);
    */

    FILE *arquivo = fopen("training.txt", "w");
    fprintf(arquivo,"%s", carrega(&first_tree, answer));
    printf("Arquivo txt contendo o treino gerado no path do código!\n");

    /* Free na memória desreferenciando o app */
    g_object_unref(app);

    return status;
}

/* Project: https://github.com/Losty17/warehouse-manager
   Author Losty17 (Vinicius Kappke) */
static GtkBuilder *get_builder_from_file(char *filename, GtkApplication *app){
    /**
     * Buffer para lidar com o nome do arquivo, para que não seja necessário
     * digitar a pasta e a extensão do arquivo ao requisitar uma tela
     */
    char path[50];
    strcpy(path, "xml/");
    strcat(path, filename);
    
    /* Cria um builder para lidar com o arquivo .ui especificado */
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, strcat(path, ".glade"), NULL);

    /* Busca a window criada no objeto e mostra ela */
    GObject *window = gtk_builder_get_object(builder, "window");

    /* Define a aplicação para a janela, caso seja especificado */
    if(app){
        gtk_window_set_application(GTK_WINDOW(window), app);
    }

    /* Mostra a janela */
    gtk_widget_show(GTK_WIDGET(window));

    /* Retorna o builder */
    return builder;
}

static void main_app_screen(GtkApplication *app, gpointer user_data){
    appdata *app_data = user_data;
    GtkWindow *window = app_data->window;
    if (window)
        gtk_window_close(window);

    /* Envia informação de qual arquivo o builder deve pegar para a montagem da window*/
    GtkBuilder *builder = get_builder_from_file("ped", app);

    /* Pega a window no builder */
    window = GTK_WINDOW(gtk_builder_get_object(builder, "window"));

    /*Dados da tela a serem enviados no momento de troca de tela,
      uma vez que a troca entre elas ocorre "fechando" uma e
      iniciando a outra.*/
    app_data->app = app;
    app_data->window = window;

    /* Referencia o botão por meio de um GObject e determina sua função callback */
    GObject *button;
    button = gtk_builder_get_object(builder, "treinosButton");
    g_signal_connect(button, "clicked", G_CALLBACK(q1_screen), app_data);
    
    //FILE *arquivo = fopen("operation.log", "a");
    //fprintf(arquivo, "%p\n", app_data->window);

    /* Descartar o builder */
    g_object_unref(builder);
}

static void q1_screen(GtkWidget *widget, gpointer data){
    appdata *app_data = data;
    gtk_window_close(app_data->window);
    
    GtkBuilder *builder = get_builder_from_file("Q1", app_data->app);
    app_data->window = GTK_WINDOW(gtk_builder_get_object(builder, "window"));

    GObject *button;

    button = gtk_builder_get_object(builder, "1dButton");
    g_signal_connect(button, "clicked", G_CALLBACK(handle_answer_d1), app_data);

    button = gtk_builder_get_object(builder, "2dButton");
    g_signal_connect(button, "clicked", G_CALLBACK(handle_answer_d2), app_data);

    button = gtk_builder_get_object(builder, "3dButton");
    g_signal_connect(button, "clicked", G_CALLBACK(handle_answer_d3), app_data);

    button = gtk_builder_get_object(builder, "4dButton");
    g_signal_connect(button, "clicked", G_CALLBACK(handle_answer_d4), app_data);

    button = gtk_builder_get_object(builder, "5dButton");
    g_signal_connect(button, "clicked", G_CALLBACK(handle_answer_d5), app_data);

    button = gtk_builder_get_object(builder, "6dButton");
    g_signal_connect(button, "clicked", G_CALLBACK(handle_answer_d6), app_data);
}

static void handle_answer_d1(GtkWidget *widget, gpointer data){
    appdata *app_data = data;
    gtk_window_close(app_data->window);

    GtkBuilder *builder = get_builder_from_file("Q2", app_data->app);
    app_data->window = GTK_WINDOW(gtk_builder_get_object(builder, "window"));

    GObject *button;
    button = gtk_builder_get_object(builder, "emagrecimentoButton");
    g_signal_connect(button, "clicked", G_CALLBACK(handle_answer_objA), app_data);

    button = gtk_builder_get_object(builder, "hipertrofiaButton");
    g_signal_connect(button, "clicked", G_CALLBACK(handle_answer_objB), app_data);

    /* Seta o valor 1 de resposta à lista de int que será recebida na árvore */
    answer[0] = 0;
}

static void handle_answer_d2(GtkWidget *widget, gpointer data){
    appdata *app_data = data;
    gtk_window_close(app_data->window);

    GtkBuilder *builder = get_builder_from_file("Q2", app_data->app);
    app_data->window = GTK_WINDOW(gtk_builder_get_object(builder, "window"));

    GObject *button;
    button = gtk_builder_get_object(builder, "emagrecimentoButton");
    g_signal_connect(button, "clicked", G_CALLBACK(handle_answer_objA), app_data);

    button = gtk_builder_get_object(builder, "hipertrofiaButton");
    g_signal_connect(button, "clicked", G_CALLBACK(handle_answer_objB), app_data);

    /* Seta o valor 1 de resposta à lista de int que será recebida na árvore */
    answer[0] = 1;
}

static void handle_answer_d3(GtkWidget *widget, gpointer data){
    appdata *app_data = data;
    gtk_window_close(app_data->window);

    GtkBuilder *builder = get_builder_from_file("Q2", app_data->app);
    app_data->window = GTK_WINDOW(gtk_builder_get_object(builder, "window"));

    GObject *button;
    button = gtk_builder_get_object(builder, "emagrecimentoButton");
    g_signal_connect(button, "clicked", G_CALLBACK(handle_answer_objA), app_data);

    button = gtk_builder_get_object(builder, "hipertrofiaButton");
    g_signal_connect(button, "clicked", G_CALLBACK(handle_answer_objB), app_data);

    /* Seta o valor 1 de resposta à lista de int que será recebida na árvore */
    answer[0] = 2;
}

static void handle_answer_d4(GtkWidget *widget, gpointer data){
    appdata *app_data = data;
    gtk_window_close(app_data->window);

    GtkBuilder *builder = get_builder_from_file("Q2", app_data->app);
    app_data->window = GTK_WINDOW(gtk_builder_get_object(builder, "window"));

    GObject *button;
    button = gtk_builder_get_object(builder, "emagrecimentoButton");
    g_signal_connect(button, "clicked", G_CALLBACK(handle_answer_objA), app_data);

    button = gtk_builder_get_object(builder, "hipertrofiaButton");
    g_signal_connect(button, "clicked", G_CALLBACK(handle_answer_objB), app_data);

    answer[0] = 3;
}

static void handle_answer_d5(GtkWidget *widget, gpointer data){
    appdata *app_data = data;
    gtk_window_close(app_data->window);

    GtkBuilder *builder = get_builder_from_file("Q2", app_data->app);
    app_data->window = GTK_WINDOW(gtk_builder_get_object(builder, "window"));

    GObject *button;
    button = gtk_builder_get_object(builder, "emagrecimentoButton");
    g_signal_connect(button, "clicked", G_CALLBACK(handle_answer_objA), app_data);

    button = gtk_builder_get_object(builder, "hipertrofiaButton");
    g_signal_connect(button, "clicked", G_CALLBACK(handle_answer_objB), app_data);

    answer[0] = 4;
}

static void handle_answer_d6(GtkWidget *widget, gpointer data){
    appdata *app_data = data;
    gtk_window_close(app_data->window);

    GtkBuilder *builder = get_builder_from_file("Q2", app_data->app);
    app_data->window = GTK_WINDOW(gtk_builder_get_object(builder, "window"));

    GObject *button;
    button = gtk_builder_get_object(builder, "emagrecimentoButton");
    g_signal_connect(button, "clicked", G_CALLBACK(handle_answer_objA), app_data);

    button = gtk_builder_get_object(builder, "hipertrofiaButton");
    g_signal_connect(button, "clicked", G_CALLBACK(handle_answer_objB), app_data);

    answer[0] = 5;
}

static void handle_answer_objA(GtkWidget *widget, gpointer data){
    appdata *app_data = data;
    gtk_window_close(app_data->window);

    GtkBuilder *builder = get_builder_from_file("Q3", app_data->app);
    app_data->window = GTK_WINDOW(gtk_builder_get_object(builder, "window"));

    GObject *button;

    button = gtk_builder_get_object(builder, "yesButton");
    g_signal_connect(button, "clicked", G_CALLBACK(save_file_screen1), app_data);

    button = gtk_builder_get_object(builder, "noButton");
    g_signal_connect(button, "clicked", G_CALLBACK(save_file_screen2), app_data);

    answer[1] = 0;

}

static void handle_answer_objB(GtkWidget *widget, gpointer data){
    appdata *app_data = data;
    gtk_window_close(app_data->window);

    GtkBuilder *builder = get_builder_from_file("Q3", app_data->app);
    app_data->window = GTK_WINDOW(gtk_builder_get_object(builder, "window"));

    answer[1] = 1;

    GObject *button;

    button = gtk_builder_get_object(builder, "yesButton");
    g_signal_connect(button, "clicked", G_CALLBACK(save_file_screen1), app_data);

    button = gtk_builder_get_object(builder, "noButton");
    g_signal_connect(button, "clicked", G_CALLBACK(save_file_screen2), app_data);

}

static void save_file_screen1(GtkWidget *widget, gpointer data){
    appdata *app_data = data;
    gtk_window_close(app_data->window);

    GtkBuilder *builder = get_builder_from_file("save", app_data->app);
    app_data->window = GTK_WINDOW(gtk_builder_get_object(builder, "window"));

    GObject *button;
    button = gtk_builder_get_object(builder, "saveButton");
    g_signal_connect(button, "clicked", G_CALLBACK(export_file), app_data);

    answer[2] = 0;

}

static void save_file_screen2(GtkWidget *widget, gpointer data){
    appdata *app_data = data;
    gtk_window_close(app_data->window);

    GtkBuilder *builder = get_builder_from_file("save", app_data->app);
    app_data->window = GTK_WINDOW(gtk_builder_get_object(builder, "window"));

    GObject *button;

    button = gtk_builder_get_object(builder, "saveButton");
    g_signal_connect(button, "clicked", G_CALLBACK(export_file), app_data);
    answer[2] = 1;
}

static void export_file(GtkWidget *widget, gpointer data){
    appdata *app_data = data;
    gtk_window_close(app_data->window);

    GtkBuilder *builder = get_builder_from_file("training", app_data->app);
    app_data->window = GTK_WINDOW(gtk_builder_get_object(builder, "window"));

    GObject *button;
    button = gtk_builder_get_object(builder, "okButton");
    g_signal_connect(button, "clicked", G_CALLBACK(close_final), app_data);
    
    GtkLabel *label;
    label = GTK_LABEL(gtk_builder_get_object(builder, "trainingLabel"));
    gtk_label_set_text (GTK_LABEL (label), carrega(&first_tree, answer));

}

static void close_final(GtkWidget *widget, gpointer data){
    appdata *app_data = data;
    gtk_window_close(app_data->window);
}