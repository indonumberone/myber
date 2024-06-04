#include <gtk/gtk.h>
#include <stdio.h>
// #include <string.h>
#include "mysql_func.h"
#include "userinfo.h"
#define WINDOW_SIZE 50

void login_process_user(GtkWidget *, gpointer);
void login_as_customers(GtkWidget *, gpointer);
void login_as_admin(GtkWidget *widget, gpointer data);
void go_back_to_home(GtkWidget *, gpointer);
void go_logout_user(GtkWidget *, gpointer);
void destroy(GtkWidget *, gpointer);
void create_welcome_user_window(GtkWidget *);
void create_welcome_admin_window(GtkWidget *);
void create_login_user_window(GtkWidget *);
void create_customer_register_window(GtkWidget *parent_window);
void create_user(GtkWidget *widget, gpointer data);
void create_user_go(GtkWidget *widget, gpointer data);
void create_login_admin_window(GtkWidget *parent_window);
void show_penjualan(GtkWidget *widget, gpointer data);
void show_history_penjualan(GtkWidget *widget, gpointer data);
void logout_memory();
void print_user_info();

UserDetails current_user;
GtkWidget *customers_login_window;
GtkWidget *admin_login_window;
GtkWidget *username_entry;
GtkWidget *name_entry;
GtkWidget *password_entry;
GtkWidget *intine_window;
GtkWidget *welcome_window;
GtkWidget *customer_register_window;
GtkWidget *banner_label;
GtkWidget *content_area;

int main(int argc, char *argv[])
{
    {
        if ((connect_mysql()) == 0)
        {
            printf("[db] Berhasil terhubung ke MySQL..\n");
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

    GtkWidget *current_window = GTK_WIDGET(data);
    gtk_widget_hide(admin_login_window);

    const gchar *username = gtk_entry_get_text(GTK_ENTRY(username_entry));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(password_entry));

    if (check_user(username) == 0)
    {
        gchar *alert_block = g_strdup_printf("User tidak ditemukan");
        gtk_label_set_text(GTK_LABEL(banner_label), alert_block);
        g_free(alert_block);

        gtk_widget_show_all(admin_login_window);
    }
    else
    {

        int hasil = login_admin(username, password);
        if (hasil == 0)
        {

            gtk_widget_show_all(admin_login_window);
        }
        else if (hasil == 1)
        {
            create_welcome_admin_window(admin_login_window);
        }
    }
}
void login_process_user(GtkWidget *widget, gpointer data)
{
    static int try = 3;

    GtkWidget *current_window = GTK_WIDGET(data);
    gtk_widget_hide(customers_login_window);

    const gchar *username = gtk_entry_get_text(GTK_ENTRY(username_entry));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(password_entry));
    UserDetails user_details;

    if (check_user(username) == 0)
    {
        gchar *alert_block = g_strdup_printf("User tidak ditemukan");
        gtk_label_set_text(GTK_LABEL(banner_label), alert_block);
        g_free(alert_block);

        gtk_widget_show_all(customers_login_window);
    }
    else
    {
        int hasil = login_user(username, password, &user_details);
        g_print("Username: %s\n", username);
        g_print("Password: %s\n", password);
        if (try < 1)
        {

            blocked(username);
            gchar *alert_block = g_strdup_printf("Anda di blokir! Tunggu beberapa menit");
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
            current_user = user_details;
            create_welcome_user_window(customers_login_window);
        }

        printf("hasil %d try %d\n", hasil, try);
    }
}

void create_user(GtkWidget *widget, gpointer data)
{
    GtkWidget *current_window = GTK_WIDGET(data);
    gtk_widget_hide(current_window);

    const gchar *username = gtk_entry_get_text(GTK_ENTRY(username_entry));
    const gchar *name = gtk_entry_get_text(GTK_ENTRY(name_entry));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(password_entry));

    g_print("Username: %s\n", username);
    g_print("Name: %s\n", name);
    g_print("Password: %s\n", password);

    register_user(username, name, password);

    printf("User: %s, Pw: %s", username, password);

    create_login_user_window(current_window);

    gchar *alert_block = g_strdup_printf("Berhasil register, silahkan login!");
    gtk_label_set_text(GTK_LABEL(banner_label), alert_block);
    g_free(alert_block);

    gtk_widget_show_all(customers_login_window);
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
    g_signal_connect(G_OBJECT(login_button), "clicked", G_CALLBACK(create_user), customer_register_window);
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

void go_logout_user(GtkWidget *widget, gpointer data)
{
    logout_memory();
}

void print_user_info()
{
    printf("User: %s\n", current_user.username);
    printf("Nama: %s\n", current_user.name);
    printf("IsAdmin: %d\n", current_user.is_admin);
}

void logout_memory()
{
    memset(&current_user, 0, sizeof(UserDetails));
}

void show_penjualan(GtkWidget *widget, gpointer data)
{
    gtk_label_set_text(GTK_LABEL(content_area), "Ini adalah halaman Penjualan.");
}

void show_history_penjualan(GtkWidget *widget, gpointer data)
{
    gtk_label_set_text(GTK_LABEL(content_area), "Ini adalah halaman History Penjualan.");
}

void create_welcome_user_window(GtkWidget *parent_window)
{

    GtkWidget *vbox;
    GtkWidget *vbox2;
    GtkWidget *label;
    GtkWidget *welcome_window;
    GtkWidget *stackSideBar;
    GtkWidget *grid;
    GtkWidget *stack;
    GtkWidget *penjualan_button;
    GtkWidget *history_penjualan_button;
    GtkWidget *testarray;

    welcome_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(welcome_window), "Welcome Window");
    gtk_window_set_default_size(GTK_WINDOW(welcome_window), 900, 600);
    gtk_container_set_border_width(GTK_CONTAINER(welcome_window), 10);

    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_container_add(GTK_CONTAINER(welcome_window), grid);

    stackSideBar = gtk_stack_sidebar_new();
    gtk_grid_attach(GTK_GRID(grid), stackSideBar, 0, 0, 1, 1);

    stack = gtk_stack_new();
    gtk_grid_attach(GTK_GRID(grid), stack, 1, 0, 1, 1);

    gtk_stack_sidebar_set_stack(GTK_STACK_SIDEBAR(stackSideBar), GTK_STACK(stack));
    // dikek i banner gambar
    // testarray[1] = gtk_label_new("iki array ke 1");
    // testarray[2] = gtk_label_new("iki array ke 2");
    char selamat_datang[256];
    sprintf(selamat_datang, "Selamat datang, %s!", current_user.name);
    label = gtk_label_new(NULL);
    gtk_label_set_text(GTK_LABEL(label), selamat_datang);
    PangoAttrList *attr_list = pango_attr_list_new();
    PangoAttribute *attr_size = pango_attr_size_new_absolute(20 * PANGO_SCALE);
    pango_attr_list_insert(attr_list, attr_size);
    gtk_label_set_attributes(GTK_LABEL(label), attr_list);
    pango_attr_list_unref(attr_list);
    GtkWidget *tanggalan = gtk_calendar_new();
    GtkWidget *image = gtk_image_new_from_file("assets/logo_welcome.png");
    gtk_box_pack_start(GTK_BOX(grid), image, TRUE, TRUE, 0);
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *welcom = gtk_label_new("Welcome!");
    banner_label = gtk_label_new("test");

    vbox2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_pack_start(GTK_BOX(vbox2), image, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox2), label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox2), tanggalan, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(vbox), banner_label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), welcom, TRUE, TRUE, 0);
    gtk_stack_add_named(GTK_STACK(stack), vbox2, "home");

    penjualan_button = gtk_button_new_with_label("Penjualan");
    g_signal_connect(G_OBJECT(penjualan_button), "clicked", G_CALLBACK(show_penjualan), NULL);

    history_penjualan_button = gtk_button_new_with_label("History");
    g_signal_connect(G_OBJECT(history_penjualan_button), "clicked", G_CALLBACK(show_history_penjualan), NULL);

    gtk_stack_add_titled(GTK_STACK(stack), vbox, "menu1", "menu ke 1");

    gtk_stack_add_titled(GTK_STACK(stack), penjualan_button, "menu2", "menu ke 2");

    g_signal_connect(welcome_window, "destroy", G_CALLBACK(destroy), NULL);
    gtk_widget_show_all(welcome_window);
}

void create_welcome_admin_window(GtkWidget *parent_window)
{

    GtkWidget *data_history;
    GtkWidget *data_input;
    GtkWidget *hdata_history;
    GtkWidget *hdata_input;
    GtkWidget *testinput;
    GtkWidget *label;
    GtkWidget *welcome_window;
    GtkWidget *stackSideBar;
    GtkWidget *grid;
    GtkWidget *stack;
    GtkWidget *penjualan_button;
    GtkWidget *history_penjualan_button;
    GtkWidget *testarray;

    welcome_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(welcome_window), "Admin Panel");
    gtk_window_set_default_size(GTK_WINDOW(welcome_window), 900, 600);
    gtk_container_set_border_width(GTK_CONTAINER(welcome_window), 10);

    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_container_add(GTK_CONTAINER(welcome_window), grid);

    stackSideBar = gtk_stack_sidebar_new();
    gtk_grid_attach(GTK_GRID(grid), stackSideBar, 0, 0, 1, 5);

    stack = gtk_stack_new();
    gtk_grid_attach(GTK_GRID(grid), stack, 1, 0, 4, 4);
    gtk_stack_sidebar_set_stack(GTK_STACK_SIDEBAR(stackSideBar), GTK_STACK(stack));

    // dikek i banner gambar
    // testarray[1] = gtk_label_new("iki array ke 1");
    // testarray[2] = gtk_label_new("iki array ke 2");
    char selamat_datang[256];
    sprintf(selamat_datang, "Selamat datang admin, %s!", current_user.name);
    label = gtk_label_new(NULL);
    gtk_label_set_text(GTK_LABEL(label), selamat_datang);
    PangoAttrList *attr_list = pango_attr_list_new();
    PangoAttribute *attr_size = pango_attr_size_new_absolute(20 * PANGO_SCALE);
    pango_attr_list_insert(attr_list, attr_size);
    gtk_label_set_attributes(GTK_LABEL(label), attr_list);
    pango_attr_list_unref(attr_list);

    hdata_history = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    hdata_input = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    data_input = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    data_history = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(data_input), hdata_input, TRUE, FALSE, 0);

    GtkWidget *image = gtk_image_new_from_file("assets/logo_welcome.png");
    gtk_box_pack_start(GTK_BOX(grid), image, TRUE, TRUE, 0);

    banner_label = gtk_label_new("tes iput:");
    testinput = gtk_entry_new();
    GtkWidget *test11 = gtk_label_new("tes iput:");
    GtkWidget *test1 = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hdata_input), banner_label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hdata_input), testinput, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hdata_input), test11, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hdata_input), test1, TRUE, TRUE, 0);

    // gtk_box_pack_start(GTK_BOX(data_history), image, TRUE, TRUE, 0);
    // gtk_box_pack_start(GTK_BOX(data_history), label, TRUE, TRUE, 0);

    // gtk_box_pack_start(GTK_BOX(data_input), banner_label, TRUE, TRUE, 0);
    // gtk_box_pack_start(GTK_BOX(data_input), welcom, TRUE, TRUE, 0);
    // gtk_stack_add_named(GTK_STACK(stack), vbox2, "home");

    gtk_stack_add_titled(GTK_STACK(stack), data_input, "inputdata", "input data penerbangan");

    gtk_stack_add_titled(GTK_STACK(stack), data_history, "historydata", "history data users");

    g_signal_connect(welcome_window, "destroy", G_CALLBACK(destroy), NULL);
    gtk_widget_show_all(welcome_window);
}

void destroy(GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}
