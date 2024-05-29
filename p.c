#include <gtk/gtk.h>

#define WINDOW_SIZE 50

void login(GtkWidget *, gpointer);
void destroy(GtkWidget *, gpointer);
void create_welcome_window(GtkWidget *);

GtkWidget *username_entry;
GtkWidget *password_entry;
GtkWidget *login_window;

int main(int argc, char *argv[])
{
    GtkWidget *vbox;
    GtkWidget *username_label;
    GtkWidget *password_label;
    GtkWidget *login_button;

    gtk_init(&argc, &argv);
    login_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    g_signal_connect(login_window, "destroy", G_CALLBACK(destroy), NULL);

    gtk_container_set_border_width(GTK_CONTAINER(login_window), WINDOW_SIZE);

    // Create a vertical box container
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(login_window), vbox);

    // Create username label and entry
    username_label = gtk_label_new("Username:");
    username_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), username_label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), username_entry, TRUE, TRUE, 0);

    // Create password label and entry
    password_label = gtk_label_new("Password:");
    password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE); // Hide text for password entry
    gtk_box_pack_start(GTK_BOX(vbox), password_label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), password_entry, TRUE, TRUE, 0);

    // Create login button
    login_button = gtk_button_new_with_label("Login");
    g_signal_connect(G_OBJECT(login_button), "clicked", G_CALLBACK(login), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), login_button, TRUE, TRUE, 0);

    gtk_widget_show_all(login_window);
    gtk_main();

    return 0;
}

void login(GtkWidget *widget, gpointer data)
{
    const gchar *username = gtk_entry_get_text(GTK_ENTRY(username_entry));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(password_entry));

    // For simplicity, assume the login is always successful
    // Here you would typically check the username and password
    g_print("Username: %s\n", username);
    g_print("Password: %s\n", password);

    // Hide the login window
    gtk_widget_hide(login_window);

    // Create and show the welcome window
    create_welcome_window(login_window);
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