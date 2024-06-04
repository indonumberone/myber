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
void insertmaskapai(GtkWidget *nama_maskapai_entry, GtkTreeIter list_maskapai);

typedef struct
{
    GtkWidget *no_penerbangan;
    GtkWidget *nama_maskapai_entry;
    GtkWidget *kelas;
    GtkWidget *asal;
    GtkWidget *tujuan;
    GtkWidget *jadwal_button;
    GtkWidget *jam_spinner;
    GtkWidget *menit_spinner;
    GtkWidget *jam_tiba;
    GtkWidget *waktu_tiba;
    GtkWidget *harga;
} FormData;

FormData current_data;
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
GtkWidget *no_penerbangan;
GtkWidget *nama_maskapai_entry;
GtkWidget *kelas;
GtkWidget *asal;
GtkWidget *tujuan;

GtkWidget *jadwal_keberangakatan_button;
GtkWidget *jam_spinner;
GtkWidget *menit_spinner;
GtkWidget *jam_tiba;
GtkWidget *waktu_tiba;
GtkWidget *harga;

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

void show_calendar(GtkWidget *button, gpointer data)
{
    GtkWidget *dialog, *calendar;
    GtkWindow *parent = GTK_WINDOW(data);

    dialog = gtk_dialog_new_with_buttons("pilih tanggale", parent, GTK_DIALOG_MODAL, "OK", GTK_RESPONSE_OK, "Cancel", GTK_RESPONSE_CANCEL, NULL);
    calendar = gtk_calendar_new();
    gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(dialog))), calendar, FALSE, FALSE, 0);
    gtk_widget_show_all(dialog);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_OK)
    {
        guint year, month, day;
        gtk_calendar_get_date(GTK_CALENDAR(calendar), &year, &month, &day);
        char date_str[11];
        sprintf(date_str, "%02d/%02d/%04d", day, month + 1, year);
        gtk_button_set_label(GTK_BUTTON(button), date_str);
    }

    gtk_widget_destroy(dialog);
}

void on_save_button_clicked(GtkWidget *button, gpointer data)
{
    // FormData *form_data = (FormData *)data;

    const gchar *nama_maskapai = gtk_entry_get_text(GTK_ENTRY(nama_maskapai_entry));
    const gchar *jadwal = gtk_button_get_label(GTK_BUTTON(jadwal_keberangakatan_button));
    gint jam = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jam_spinner));
    gint menit = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(menit_spinner));

    g_print("maskapai: %s\n", nama_maskapai);
    g_print("jadwal: %s\n", jadwal);
    g_print("jame: %02d:%02d\n", jam, menit);
}

// void insertmaskapai(GtkWidget **nama_maskapai_entry, GtkTreeIter **list_maskapai)
// {

//     gtk_list_store_append(nama_maskapai_entry, *list_maskapai);
//     gtk_list_store_set(nama_maskapai_entry, *list_maskapai, 0, "Lion Air", -1);
//     gtk_list_store_append(nama_maskapai_entry, *list_maskapai);
//     gtk_list_store_set(nama_maskapai_entry, *list_maskapai, 0, "Wings Air", -1);
//     gtk_list_store_append(nama_maskapai_entry, *list_maskapai);
//     gtk_list_store_set(nama_maskapai_entry, *list_maskapai, 0, "Citilink", -1);
//     gtk_list_store_append(nama_maskapai_entry, *list_maskapai);
//     gtk_list_store_set(nama_maskapai_entry, *list_maskapai, 0, "Garuda Indonesia", -1);
//     gtk_list_store_append(nama_maskapai_entry, *list_maskapai);
//     gtk_list_store_set(nama_maskapai_entry, *list_maskapai, 0, "Batik Air", -1);
//     gtk_list_store_append(nama_maskapai_entry, *list_maskapai);
//     gtk_list_store_set(nama_maskapai_entry, *list_maskapai, 0, "Sriwijaya Air", -1);
//     gtk_list_store_append(nama_maskapai_entry, *list_maskapai);
//     gtk_list_store_set(nama_maskapai_entry, *list_maskapai, 0, "AirAsia", -1);
// }

GtkWidget *create_input_data_page(GtkWidget *parent_window, FormData *form_data)
{
    GtkWidget *no_penerbangan_pesawat_entry;
    GtkWidget *nama_maskapai_mark;
    GtkListStore *nama_maskapai_entry;
    GtkCellRenderer *renderer_maskapai;
    GtkTreeIter list_maskapai;

    GtkWidget *nama_kelas_mark;
    GtkWidget *kelas_mark;
    GtkListStore *kelas_entry;
    GtkCellRenderer *renderer_kelas;
    GtkWidget *nama_asal_entry;
    GtkWidget *nama_tujuan_entry;
    GtkTreeIter list_kelas;

    GtkWidget *data_input = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    GtkWidget *no_penerbangan_pesawat_label = gtk_label_new("No Penerbangan");
    no_penerbangan_pesawat_entry = gtk_entry_new();
    GtkWidget *nama_maskapai_label = gtk_label_new("Nama Maskapai");
    GtkWidget *nama_kelas_label = gtk_label_new("Jenis Kelas Pesawat");
    GtkWidget *nama_asal_label = gtk_label_new("keberangkatan Pesawat ");
    GtkWidget *nama_tujuan_label = gtk_label_new("Kedatangan Pesawat ");
    nama_asal_entry = gtk_entry_new();
    nama_tujuan_entry = gtk_entry_new();
    // menuBar = gtk_menu_bar_new();
    // /* create 1st menu item */
    // menuItem1 = gtk_menu_item_new_with_mnemonic("_Application");
    // /* add the submenu for the 1st menu item */
    // submenu1 = gtk_menu_new();
    // /* add the message item */
    // item_message = gtk_menu_item_new_with_label("Message");
    // /* add the quit item menu for the submenu */
    // item_quit = gtk_menu_item_new_with_label("Quit");
    // /* create the list model for the combo */
    nama_maskapai_entry = gtk_list_store_new(1, G_TYPE_STRING);
    // insertmaskapai(nama_maskapai_entry, &list_maskapai);
    gtk_list_store_append(nama_maskapai_entry, &list_maskapai);
    gtk_list_store_set(nama_maskapai_entry, &list_maskapai, 0, "Lion Air", -1);
    gtk_list_store_append(nama_maskapai_entry, &list_maskapai);
    gtk_list_store_set(nama_maskapai_entry, &list_maskapai, 0, "Wings Air", -1);
    gtk_list_store_append(nama_maskapai_entry, &list_maskapai);
    gtk_list_store_set(nama_maskapai_entry, &list_maskapai, 0, "Citilink", -1);
    gtk_list_store_append(nama_maskapai_entry, &list_maskapai);
    gtk_list_store_set(nama_maskapai_entry, &list_maskapai, 0, "Garuda Indonesia", -1);
    gtk_list_store_append(nama_maskapai_entry, &list_maskapai);
    gtk_list_store_set(nama_maskapai_entry, &list_maskapai, 0, "Batik Air", -1);
    gtk_list_store_append(nama_maskapai_entry, &list_maskapai);
    gtk_list_store_set(nama_maskapai_entry, &list_maskapai, 0, "Sriwijaya Air", -1);
    gtk_list_store_append(nama_maskapai_entry, &list_maskapai);
    gtk_list_store_set(nama_maskapai_entry, &list_maskapai, 0, "AirAsia", -1);
    nama_maskapai_mark = gtk_combo_box_new_with_model(GTK_TREE_MODEL(nama_maskapai_entry));
    g_object_unref(nama_maskapai_entry);
    renderer_maskapai = gtk_cell_renderer_text_new();
    gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(nama_maskapai_mark), renderer_maskapai, TRUE);
    gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(nama_maskapai_mark), renderer_maskapai, "text", 0, NULL);
    gtk_combo_box_set_active(GTK_COMBO_BOX(nama_maskapai_mark), 0);

    kelas_entry = gtk_list_store_new(1, G_TYPE_STRING);

    gtk_list_store_append(kelas_entry, &list_kelas);
    gtk_list_store_set(kelas_entry, &list_kelas, 0, "Ekonomi", -1);
    gtk_list_store_append(kelas_entry, &list_kelas);
    gtk_list_store_set(kelas_entry, &list_kelas, 0, "Bussines", -1);

    nama_kelas_mark = gtk_combo_box_new_with_model(GTK_TREE_MODEL(kelas_entry));

    g_object_unref(kelas_entry);
    renderer_kelas = gtk_cell_renderer_text_new();
    gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(nama_kelas_mark), renderer_kelas, TRUE);
    gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(nama_kelas_mark), renderer_kelas, "text", 0, NULL);
    gtk_combo_box_set_active(GTK_COMBO_BOX(nama_kelas_mark), 0);

    GtkWidget *jadwal_keberangakatan_label = gtk_label_new("Jadwal Penerbangan:");
    jadwal_keberangakatan_button = gtk_button_new_with_label("tanggale");
    g_signal_connect(jadwal_keberangakatan_button, "clicked", G_CALLBACK(show_calendar), parent_window);

    GtkWidget *jam_keberangakatan_label = gtk_label_new("Jam Penerbangan:");
    jam_spinner = gtk_spin_button_new_with_range(0, 23, 1);
    menit_spinner = gtk_spin_button_new_with_range(0, 59, 1);

    GtkWidget *save_button = gtk_button_new_with_label("Simpan");
    g_signal_connect(save_button, "clicked", G_CALLBACK(on_save_button_clicked), form_data);
    GtkWidget *waktu_keberangakatan = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    GtkWidget *waktu_kedatangan = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);

    gtk_box_pack_start(GTK_BOX(data_input), no_penerbangan_pesawat_label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(data_input), no_penerbangan_pesawat_entry, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(data_input), nama_maskapai_label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(data_input), nama_maskapai_mark, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(data_input), nama_kelas_label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(data_input), nama_kelas_mark, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(data_input), nama_asal_label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(data_input), nama_asal_entry, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(data_input), nama_tujuan_label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(data_input), nama_tujuan_entry, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(data_input), jadwal_keberangakatan_label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(data_input), jadwal_keberangakatan_button, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(data_input), jam_keberangakatan_label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(data_input), waktu_keberangakatan, FALSE, FALSE, 5);
    // gtk_box_set_center_widget(data_input, waktu);
    // gtk_box_get_center_widget(waktu);
    gtk_box_pack_start(GTK_BOX(waktu_keberangakatan), jam_spinner, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(waktu_keberangakatan), menit_spinner, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(data_input), save_button, FALSE, FALSE, 5);
    // g_signal_connect(nama_maskapai_entry, "changed", G_CALLBACK(cb_combo_change), NULL);
    return data_input;
}

// GtkWidget *create_input_data_page_gaksido(GtkWidget *parent_window)
// {
//     GtkWidget *data_input = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);

//     GtkWidget *nama_maskapai_label = gtk_label_new("Nama Maskapai:");
//     GtkWidget *nama_maskapai_entry = gtk_entry_new();

//     GtkWidget *jadwal_label = gtk_label_new("Jadwal Penerbangan:");
//     GtkWidget *jadwal_button = gtk_button_new_with_label("Pilih Tanggal");
//     g_signal_connect(jadwal_button, "clicked", G_CALLBACK(show_calendar), parent_window);

//     GtkWidget *jam_label = gtk_label_new("Jam Penerbangan:");
//     GtkWidget *jam_spinner = gtk_spin_button_new_with_range(0, 23, 1);
//     GtkWidget *menit_spinner = gtk_spin_button_new_with_range(0, 59, 1);

//     gtk_box_pack_start(GTK_BOX(data_input), nama_maskapai_label, FALSE, FALSE, 5);
//     gtk_box_pack_start(GTK_BOX(data_input), nama_maskapai_entry, FALSE, FALSE, 5);
//     gtk_box_pack_start(GTK_BOX(data_input), jadwal_label, FALSE, FALSE, 5);
//     gtk_box_pack_start(GTK_BOX(data_input), jadwal_button, FALSE, FALSE, 5);
//     gtk_box_pack_start(GTK_BOX(data_input), jam_label, FALSE, FALSE, 5);
//     gtk_box_pack_start(GTK_BOX(data_input), jam_spinner, FALSE, FALSE, 5);
//     gtk_box_pack_start(GTK_BOX(data_input), menit_spinner, FALSE, FALSE, 5);

//     return data_input;
// }

// GtkWidget *create_input_data_page()
// {
//     GtkWidget *data_input = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
//     GtkWidget *hdata_input = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);

//     GtkWidget *banner_label = gtk_label_new("tes iput:");
//     GtkWidget *testinput = gtk_entry_new();
//     GtkWidget *test11 = gtk_label_new("tes iput:");
//     GtkWidget *test1 = gtk_entry_new();

//     gtk_box_pack_start(GTK_BOX(hdata_input), banner_label, TRUE, TRUE, 0);
//     gtk_box_pack_start(GTK_BOX(hdata_input), testinput, TRUE, TRUE, 0);
//     gtk_box_pack_start(GTK_BOX(hdata_input), test11, TRUE, TRUE, 0);
//     gtk_box_pack_start(GTK_BOX(hdata_input), test1, TRUE, TRUE, 0);

//     gtk_box_pack_start(GTK_BOX(data_input), hdata_input, TRUE, FALSE, 0);

//     return data_input;
// }

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

    FormData form_data;

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
    GtkWidget *testh = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    hdata_history = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    hdata_input = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    data_input = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    data_history = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    gtk_box_pack_start(GTK_BOX(data_input), hdata_input, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(data_input), testh, TRUE, FALSE, 0);
    penjualan_button = gtk_button_new_with_label("Penjualan");
    g_signal_connect(G_OBJECT(penjualan_button), "clicked", G_CALLBACK(show_penjualan), NULL);

    gtk_box_pack_start(GTK_BOX(data_input), testh, TRUE, FALSE, 0);
    GtkWidget *image = gtk_image_new_from_file("assets/logo_welcome.png");
    gtk_box_pack_start(GTK_BOX(grid), image, TRUE, TRUE, 0);

    banner_label = gtk_label_new("tes iput:");
    testinput = gtk_entry_new();
    GtkWidget *test11 = gtk_label_new("tes iput:");
    GtkWidget *test1 = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hdata_input), banner_label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hdata_input), testinput, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(testh), test11, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(testh), test1, TRUE, TRUE, 0);

    // gtk_box_pack_start(GTK_BOX(data_history), image, TRUE, TRUE, 0);
    // gtk_box_pack_start(GTK_BOX(data_history), label, TRUE, TRUE, 0);

    // gtk_box_pack_start(GTK_BOX(data_input), banner_label, TRUE, TRUE, 0);
    // gtk_box_pack_start(GTK_BOX(data_input), welcom, TRUE, TRUE, 0);
    // gtk_stack_add_named(GTK_STACK(stack), vbox2, "home");
    GtkWidget *input_data_page = create_input_data_page(welcome_window, &form_data);
    // GtkWidget *input_data_page = create_input_data_page();
    gtk_stack_add_titled(GTK_STACK(stack), input_data_page, "inputdata", "Input Data Penerbangan");

    // gtk_stack_add_titled(GTK_STACK(stack), data_input, "inputdata", "input data penerbangan");

    gtk_stack_add_titled(GTK_STACK(stack), data_input, "historydata", "Riwayat Transaksi");

    g_signal_connect(welcome_window, "destroy", G_CALLBACK(destroy), NULL);
    gtk_widget_show_all(welcome_window);
}

void destroy(GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}
