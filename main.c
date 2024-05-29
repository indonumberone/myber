#include <gtk/gtk.h>
#include <stdio.h>
// #include <string.h>
#include "mysql_func.h"
#define WINDOW_SIZE 50

void loginin(GtkWidget *, gpointer);
void login_as_customers(GtkWidget *, gpointer);
void destroy(GtkWidget *, gpointer);
void create_welcome_window(GtkWidget *);
void create_customers_login_window(GtkWidget *);

GtkWidget *username_entry;
GtkWidget *password_entry;
GtkWidget *login_window;

int main(int argc, char *argv[]) {
{
    if ((connect_mysql()) == 0)
    {
        printf("sukses");
    }
      }
    GtkWidget *vbox;
    GtkWidget *username_label;
    GtkWidget *password_label;
    GtkWidget *login_customers_button;
    GtkWidget *login_admin_button;
    GtkWidget *image;
    GtkWidget *banner_label;

    gtk_init(&argc, &argv);
    login_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    g_signal_connect(login_window, "destroy", G_CALLBACK(destroy), NULL);

    gtk_container_set_border_width(GTK_CONTAINER(login_window), WINDOW_SIZE);

    gtk_window_set_default_size(GTK_WINDOW(login_window), 400, 300);
    gtk_window_set_resizable(GTK_WINDOW(login_window), TRUE);

    // Create a vertical box container
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(login_window), vbox);

    // dikek i banner gambar
    image = gtk_image_new_from_file("assets/banner.png");
    gtk_box_pack_start(GTK_BOX(vbox), image, TRUE, TRUE, 0);

    banner_label = gtk_label_new("Selamat Datang di Myber-Indonesia!");
    PangoAttrList *attr_list = pango_attr_list_new();
    PangoAttribute *attr_size = pango_attr_size_new_absolute(30 * PANGO_SCALE); // Set size to 20
    pango_attr_list_insert(attr_list, attr_size);
    gtk_label_set_attributes(GTK_LABEL(banner_label), attr_list);
    pango_attr_list_unref(attr_list);
    gtk_box_pack_start(GTK_BOX(vbox), banner_label, TRUE, TRUE, 0);

    // Create login button
    login_customers_button = gtk_button_new_with_label("Login sebagai customers");
    g_signal_connect(G_OBJECT(login_customers_button), "clicked", G_CALLBACK(login_as_customers), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), login_customers_button, TRUE, TRUE, 0);

    login_customers_button = gtk_button_new_with_label("Login sebagai admin");
    g_signal_connect(G_OBJECT(login_customers_button), "clicked", G_CALLBACK(loginin), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), login_customers_button, TRUE, TRUE, 0);

    gtk_widget_show_all(login_window);
    gtk_main();

    return 0;
}

void login_as_customers(GtkWidget *widget, gpointer data) {
    gtk_widget_hide(login_window);
    create_customers_login_window(login_window);
}

void loginin(GtkWidget *widget, gpointer data)
{
    const gchar *username = gtk_entry_get_text(GTK_ENTRY(username_entry));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(password_entry));

    g_print("Username: %s\n", username);
    g_print("Password: %s\n", password);

    int hasil = register_user(username, username, password);
    printf("hasil %d\n", hasil);

    // printf("User: %s, Pw: %s", username, password);

    gtk_widget_hide(login_window);
    create_welcome_window(login_window);
}

void create_customers_login_window(GtkWidget *parent_window)
{
        GtkWidget *customers_login_window;
        GtkWidget *vbox;
        GtkWidget *username_label;
        GtkWidget *password_label;
        GtkWidget *login_button;
        GtkWidget *image;
        GtkWidget *banner_label;

        customers_login_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

        g_signal_connect(customers_login_window, "destroy", G_CALLBACK(destroy), NULL);

        gtk_container_set_border_width(GTK_CONTAINER(customers_login_window), WINDOW_SIZE);

        vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
        gtk_container_add(GTK_CONTAINER(customers_login_window), vbox);

        // dikek i banner gambar
        image = gtk_image_new_from_file("assets/login_cust.png");
        gtk_box_pack_start(GTK_BOX(vbox), image, TRUE, TRUE, 0);

        banner_label = gtk_label_new("Silahkan Login!");
        PangoAttrList *attr_list = pango_attr_list_new();
        PangoAttribute *attr_size = pango_attr_size_new_absolute(30 * PANGO_SCALE); 
        pango_attr_list_insert(attr_list, attr_size);
        gtk_label_set_attributes(GTK_LABEL(banner_label), attr_list);
        pango_attr_list_unref(attr_list);
        gtk_box_pack_start(GTK_BOX(vbox), banner_label, TRUE, TRUE, 0);

        username_label = gtk_label_new("Username:");
        username_entry = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(vbox), username_label, TRUE, TRUE, 0);
        gtk_box_pack_start(GTK_BOX(vbox), username_entry, TRUE, TRUE, 0);

        password_label = gtk_label_new("Password:");
        password_entry = gtk_entry_new();
        gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE); 
        gtk_box_pack_start(GTK_BOX(vbox), password_label, TRUE, TRUE, 0);
        gtk_box_pack_start(GTK_BOX(vbox), password_entry, TRUE, TRUE, 0);

        login_button = gtk_button_new_with_label("Login");
        g_signal_connect(G_OBJECT(login_button), "clicked", G_CALLBACK(loginin), NULL);
        gtk_box_pack_start(GTK_BOX(vbox), login_button, TRUE, TRUE, 0);

        gtk_widget_show_all(customers_login_window);
}

void create_welcome_window(GtkWidget *parent_window)
{
    GtkWidget *welcome_window;
    GtkWidget *vbox;
    GtkWidget *label;

    welcome_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    g_signal_connect(welcome_window, "destroy", G_CALLBACK(destroy), NULL);

    gtk_container_set_border_width(GTK_CONTAINER(welcome_window), WINDOW_SIZE);

    // Create a vertical box container
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(welcome_window), vbox);

    // Create welcome label
    label = gtk_label_new("Welcome!");
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);

    gtk_widget_show_all(welcome_window);
}


void destroy(GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}

// Compile with: gcc -o login_example login_example.c `pkg-config --cflags --libs gtk+-3.0`