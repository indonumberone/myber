#include <gtk/gtk.h>
#include <stdio.h>
// #include <string.h>
#include "mysql_func.h"
#define WINDOW_SIZE 50

// void myCSS(void);
void login_process_user(GtkWidget *, gpointer);
void login_as_customers(GtkWidget *, gpointer);
void login_as_admin(GtkWidget *widget, gpointer data);
void login_admin_process_user(GtkWidget *widget, gpointer data);
void go_back_to_home(GtkWidget *, gpointer);
void destroy(GtkWidget *, gpointer);
void create_welcome_window(GtkWidget *);
void create_login_user_window(GtkWidget *);
void create_customer_register_window(GtkWidget *parent_window);
void create_user(GtkWidget *widget, gpointer data);
void create_user_go(GtkWidget *widget, gpointer data);
void create_login_admin_window(GtkWidget *parent_window);

GtkWidget *customers_login_window;
GtkWidget *admin_login_window;
GtkWidget *username_entry;
GtkWidget *name_entry;
GtkWidget *password_entry;
GtkWidget *intine_window;
GtkWidget *welcome_window;
GtkWidget *customer_register_window;
GtkWidget *banner_label;

int main(int argc, char *argv[])
{
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

    GtkWidget *create_label;
    GtkWidget *info_label;
    GtkWidget *create_akun;
    // myCSS();
    gtk_init(&argc, &argv);
    intine_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    g_signal_connect(intine_window, "destroy", G_CALLBACK(destroy), NULL);

    gtk_container_set_border_width(GTK_CONTAINER(intine_window), WINDOW_SIZE);

    gtk_window_set_default_size(GTK_WINDOW(intine_window), 400, 300);
    gtk_window_set_resizable(GTK_WINDOW(intine_window), TRUE);

    // Create a vertical box container
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(intine_window), vbox);

    // dikek i banner gambar
    image = gtk_image_new_from_file("assets/banner.png");
    gtk_box_pack_start(GTK_BOX(vbox), image, TRUE, TRUE, 0);

    banner_label = gtk_label_new("Selamat Datang di Myber-Indonesia!");
    PangoAttrList *attr_list = pango_attr_list_new();
    PangoAttribute *attr_size = pango_attr_size_new_absolute(30 * PANGO_SCALE);
    pango_attr_list_insert(attr_list, attr_size);
    gtk_label_set_attributes(GTK_LABEL(banner_label), attr_list);
    pango_attr_list_unref(attr_list);
    gtk_box_pack_start(GTK_BOX(vbox), banner_label, TRUE, TRUE, 0);

    info_label = gtk_label_new("Sudah punya akun? Silahkan login.");
    PangoAttrList *attr_list_additional = pango_attr_list_new();
    PangoAttribute *attr_size_additional = pango_attr_size_new_absolute(19 * PANGO_SCALE);
    PangoAttribute *attr_weight_additional = pango_attr_weight_new(PANGO_WEIGHT_BOLD);
    pango_attr_list_insert(attr_list_additional, attr_size_additional);
    pango_attr_list_insert(attr_list_additional, attr_weight_additional);
    gtk_label_set_attributes(GTK_LABEL(info_label), attr_list_additional);
    pango_attr_list_unref(attr_list_additional);
    gtk_box_pack_start(GTK_BOX(vbox), info_label, TRUE, TRUE, 0);

    // Create login button
    login_customers_button = gtk_button_new_with_label("LOGIN AS CUSTOMERS");
    g_signal_connect(G_OBJECT(login_customers_button), "clicked", G_CALLBACK(login_as_customers), intine_window);
    gtk_box_pack_start(GTK_BOX(vbox), login_customers_button, TRUE, TRUE, 0);
    login_admin_button = gtk_button_new_with_label("LOGIN AS ADMIN ");
    g_signal_connect(G_OBJECT(login_admin_button), "clicked", G_CALLBACK(login_as_admin), intine_window);
    gtk_box_pack_start(GTK_BOX(vbox), login_admin_button, TRUE, TRUE, 0);

    create_label = gtk_label_new("Belum Punya akun? Silahkan register");
    gtk_box_pack_start(GTK_BOX(vbox), create_label, TRUE, TRUE, 0);
    PangoAttrList *attr_list_info_lagi = pango_attr_list_new();
    PangoAttribute *attr_size_info_lagi = pango_attr_size_new_absolute(15 * PANGO_SCALE);
    PangoAttribute *attr_weight_info_lagi = pango_attr_style_new(PANGO_STYLE_ITALIC);
    pango_attr_list_insert(attr_list_info_lagi, attr_size_info_lagi);
    pango_attr_list_insert(attr_list_info_lagi, attr_weight_info_lagi);
    gtk_label_set_attributes(GTK_LABEL(create_label), attr_list_info_lagi);
    pango_attr_list_unref(attr_list_info_lagi);
    gtk_box_pack_start(GTK_BOX(vbox), create_label, TRUE, TRUE, 0);

    create_akun = gtk_button_new_with_label("BUAT AKUN");
    g_signal_connect(G_OBJECT(create_akun), "clicked", G_CALLBACK(create_user_go), intine_window);
    gtk_box_pack_start(GTK_BOX(vbox), create_akun, TRUE, TRUE, 0);

    gtk_widget_show_all(intine_window);
    gtk_main();

    return 0;
}

// void myCSS(void)
// {
//     GtkCssProvider *provider;
//     GdkDisplay *display;
//     GdkScreen *screen;

//     provider = gtk_css_provider_new();
//     display = gdk_display_get_default();
//     screen = gdk_display_get_default_screen(display);
//     gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

//     const gchar *myCssFile = "style.css";
//     GError *error = 0;

//     gtk_css_provider_load_from_file(provider, g_file_new_for_path(myCssFile), &error);
//     g_object_unref(provider);
// }

void login_as_customers(GtkWidget *widget, gpointer data)
{
    GtkWidget *current_window = GTK_WIDGET(data);
    gtk_widget_hide(current_window);
    create_login_user_window(intine_window);
}
void login_as_admin(GtkWidget *widget, gpointer data)
{
    GtkWidget *current_window = GTK_WIDGET(data);
    gtk_widget_hide(current_window);
    create_login_admin_window(intine_window);
}
void create_user_go(GtkWidget *widget, gpointer data)
{
    GtkWidget *current_window = GTK_WIDGET(data);
    gtk_widget_hide(current_window);
    create_customer_register_window(intine_window);
}
void login_process_admin(GtkWidget *widget, gpointer data)
{
    static int try = 3;

    GtkWidget *current_window = GTK_WIDGET(data);
    gtk_widget_hide(customers_login_window);

    const gchar *username = gtk_entry_get_text(GTK_ENTRY(username_entry));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(password_entry));

    int hasil = login_user(username, password);
    g_print("Username: %s\n", username);
    g_print("Password: %s\n", password);

    if (try < 1)
    {

        blocked(username);
        gchar *alert_block = g_strdup_printf("Anda di blokir!\nSilahkan coba dalam beberapa menit");
        gtk_label_set_text(GTK_LABEL(banner_label), alert_block);
        g_free(alert_block);

        gtk_widget_show_all(customers_login_window);
    }
    else if (hasil == 0)
    {
        // test = gtk_label_new(try);
        try--;
        gchar *percobaan = g_strdup_printf("Username atau Password salah!");
        gtk_label_set_text(GTK_LABEL(banner_label), percobaan);
        g_free(percobaan);
        gtk_widget_show_all(customers_login_window);
    }
    else if (hasil == 1)
    {
        create_welcome_window(customers_login_window);
    }

    printf("hasil %d try %d\n", hasil, try);

    // printf("User: %s, Pw: %s", username, password);
}
void login_process_user(GtkWidget *widget, gpointer data)
{
    static int try = 3;

    GtkWidget *current_window = GTK_WIDGET(data);
    gtk_widget_hide(customers_login_window);

    const gchar *username = gtk_entry_get_text(GTK_ENTRY(username_entry));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(password_entry));
    if (check_user(username) == 0)
    {
        printf("gak onk");
        gchar *alert_block = g_strdup_printf("User tidak ditemukan");
        gtk_label_set_text(GTK_LABEL(banner_label), alert_block);
        g_free(alert_block);

        gtk_widget_show_all(customers_login_window);
    }
    else
    {
        int hasil = login_user(username, password);
        g_print("Username: %s\n", username);
        g_print("Password: %s\n", password);
        if (try < 1)
        {

            blocked(username);
            gchar *alert_block = g_strdup_printf("Anda di blokir!\nSilahkan coba dalam beberapa menit");
            gtk_label_set_text(GTK_LABEL(banner_label), alert_block);
            g_free(alert_block);

            gtk_widget_show_all(customers_login_window);
        }
        else if (hasil == 0)
        {
            // test = gtk_label_new(try);
            try--;
            gchar *percobaan = g_strdup_printf("Username atau Password salah!");
            gtk_label_set_text(GTK_LABEL(banner_label), percobaan);
            g_free(percobaan);
            gtk_widget_show_all(customers_login_window);
        }
        else if (hasil == 1)
        {
            create_welcome_window(customers_login_window);
        }

        printf("hasil %d try %d\n", hasil, try);
    }
}

void login_admin_process_user(GtkWidget *widget, gpointer data)
{
    static int try;

    GtkWidget *current_window = GTK_WIDGET(data);
    gtk_widget_hide(customers_login_window);

    const gchar *username = gtk_entry_get_text(GTK_ENTRY(username_entry));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(password_entry));
    if (try > 2)
    {
        blocked(username);
        printf("hayooo");
    }
    g_print("Username: %s\n", username);
    g_print("Password: %s\n", password);

    int hasil = login_user(username, password);
    if (hasil == 0)
    {
        // test = gtk_label_new(try);
        try++;
        gtk_widget_show_all(customers_login_window);
    }
    else if (hasil == 1)
    {
        create_welcome_window(customers_login_window);
    }

    printf("hasil %d try %d\n", hasil, try);

    // printf("User: %s, Pw: %s", username, password);
}

void create_user(GtkWidget *widget, gpointer data)
{
    GtkWidget *current_window = GTK_WIDGET(data);
    gtk_widget_hide(customers_login_window);

    const gchar *username = gtk_entry_get_text(GTK_ENTRY(username_entry));
    const gchar *name = gtk_entry_get_text(GTK_ENTRY(name_entry));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(password_entry));

    g_print("Username: %s\n", username);
    g_print("Name: %s\n", name);
    g_print("Password: %s\n", password);

    int hasil = register_user(username, name, password);
    printf("hasil %d\n", hasil);

    // printf("User: %s, Pw: %s", username, password);

    create_welcome_window(customers_login_window);
}

void create_login_admin_window(GtkWidget *parent_window)
{
    GtkWidget *vbox;
    GtkWidget *username_label;
    GtkWidget *password_label;
    GtkWidget *login_button;
    GtkWidget *back_button;
    GtkWidget *image;

    // printf("apalah %s\n", parent_window);
    admin_login_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(admin_login_window, "destroy", G_CALLBACK(destroy), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(admin_login_window), WINDOW_SIZE);
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(admin_login_window), vbox);
    // dikek i banner gambar
    image = gtk_image_new_from_file("assets/login_admin.png");
    gtk_box_pack_start(GTK_BOX(vbox), image, TRUE, TRUE, 0);

    banner_label = gtk_label_new("Silahkan Login Sebagai Admin");
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
    g_signal_connect(G_OBJECT(login_button), "clicked", G_CALLBACK(login_process_admin), admin_login_window);
    gtk_box_pack_start(GTK_BOX(vbox), login_button, TRUE, TRUE, 0);

    back_button = gtk_button_new_with_label("Kembali ke halaman awal");
    g_signal_connect(G_OBJECT(back_button), "clicked", G_CALLBACK(go_back_to_home), admin_login_window);
    gtk_box_pack_start(GTK_BOX(vbox), back_button, TRUE, TRUE, 0);

    gtk_widget_show_all(admin_login_window);
}

void create_login_user_window(GtkWidget *parent_window)
{
    GtkWidget *vbox;
    GtkWidget *username_label;
    GtkWidget *password_label;
    GtkWidget *login_button;
    GtkWidget *back_button;
    GtkWidget *image;

    // printf("apalah %s\n", parent_window);
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
    g_signal_connect(G_OBJECT(login_button), "clicked", G_CALLBACK(login_process_user), customers_login_window);
    gtk_box_pack_start(GTK_BOX(vbox), login_button, TRUE, TRUE, 0);

    back_button = gtk_button_new_with_label("Kembali ke halaman awal");
    g_signal_connect(G_OBJECT(back_button), "clicked", G_CALLBACK(go_back_to_home), customers_login_window);
    gtk_box_pack_start(GTK_BOX(vbox), back_button, TRUE, TRUE, 0);

    gtk_widget_show_all(customers_login_window);
}

void create_customer_register_window(GtkWidget *parent_window)
{
    GtkWidget *vbox;
    GtkWidget *username_label;
    GtkWidget *name_label;
    GtkWidget *password_label;
    GtkWidget *login_button;
    GtkWidget *back_button;
    GtkWidget *image;

    customer_register_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(customer_register_window, "destroy", G_CALLBACK(destroy), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(customer_register_window), WINDOW_SIZE);
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(customer_register_window), vbox);
    // dikek i banner gambar
    image = gtk_image_new_from_file("assets/register_cust.png");
    gtk_box_pack_start(GTK_BOX(vbox), image, TRUE, TRUE, 0);

    banner_label = gtk_label_new("Create Your Account !!");
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
    name_label = gtk_label_new("Name:");
    name_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), name_label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), name_entry, TRUE, TRUE, 0);
    password_label = gtk_label_new("Password:");
    password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
    gtk_box_pack_start(GTK_BOX(vbox), password_label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), password_entry, TRUE, TRUE, 0);

    login_button = gtk_button_new_with_label("Create Account");
    g_signal_connect(G_OBJECT(login_button), "clicked", G_CALLBACK(create_welcome_window), customer_register_window);
    gtk_box_pack_start(GTK_BOX(vbox), login_button, TRUE, TRUE, 0);

    back_button = gtk_button_new_with_label("Kembali ke halaman awal");
    g_signal_connect(G_OBJECT(back_button), "clicked", G_CALLBACK(go_back_to_home), customer_register_window);
    gtk_box_pack_start(GTK_BOX(vbox), back_button, TRUE, TRUE, 0);

    gtk_widget_show_all(customer_register_window);
}

void go_back_to_home(GtkWidget *widget, gpointer data)
{
    GtkWidget *current_window = GTK_WIDGET(data);
    gtk_widget_hide(current_window);
    gtk_widget_show_all(intine_window);
}

void create_welcome_window(GtkWidget *parent_window)
{

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