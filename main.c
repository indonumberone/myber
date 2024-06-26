#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include "mysql_func.h"
#include "userinfo.h"
#include "flightdata.h"
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

FlightDetails current_flight;
UserDetails current_user;

GtkWidget *customers_login_window;
GtkWidget *admin_login_window;
GtkWidget *username_entry;
GtkWidget *name_entry;
GtkWidget *password_entry;
GtkWidget *intine_window;
GtkWidget *alert_warningin;

GtkWidget *welcome_window;
GtkWidget *orders_window;
GtkWidget *tickets_window;
GtkWidget *customer_register_window;
GtkWidget *banner_label;
GtkWidget *tiket_label;
GtkWidget *content_area;
GtkWidget *no_penerbangan;
GtkWidget *nama_maskapai_entry;
GtkWidget *kelas;
GtkWidget *asal;
GtkWidget *tujuan;

GtkWidget *jadwal_keberangakatan_button;
GtkWidget *no_penerbangan_pesawat_entry;
GtkWidget *nama_asal_entry;
GtkWidget *nama_tujuan_entry;
GtkWidget *jam_keberangkatan;
GtkWidget *menit_keberangkatan;
GtkWidget *jam_kedatangan;
GtkWidget *menit_kedatangan;
GtkWidget *jam_tes;
GtkWidget *jam_tiba;
GtkWidget *waktu_tiba;
GtkWidget *jadwal_kedatangan_button;
GtkWidget *waktu_datang;
GtkWidget *harga_entry;

GtkListStore *kelas_entry;
GtkTreeSelection *current_selection = NULL;

gchar *entry_maskapai;
gchar *entry_kelas;
enum
{
    FILE_NAME,
    FILE_MASKAPAI,
    FILE_KELAS,
    FILE_ASAL,
    FILE_TUJUAN,
    FILE_TGL_BERANGKAT,
    FILE_WAKTU_B,
    FILE_TGL_DATANG,
    FILE_WAKTU_T,
    FILE_HARGA,
    FILE_SIZE,
    FILE_DESCRIPTION,
    COLOR,
    N_COLUMNS
};

void maskapai_list(GtkComboBox *combo, gpointer user_data)
{
    gint index = gtk_combo_box_get_active(combo);
    if (index)
    {
        GtkTreeModel *model;
        GtkTreeIter iter;
        model = gtk_combo_box_get_model(combo);
        gtk_tree_model_iter_nth_child(model, &iter, NULL, index);
        gtk_tree_model_get(model, &iter, 0, &entry_maskapai, -1);
    }
}

void kelas_list(GtkComboBox *combo, gpointer user_data)
{
    gint index = gtk_combo_box_get_active(combo);
    if (index)
    {
        GtkTreeModel *model;
        GtkTreeIter iter;
        model = gtk_combo_box_get_model(combo);
        gtk_tree_model_iter_nth_child(model, &iter, NULL, index);
        gtk_tree_model_get(model, &iter, 0, &entry_kelas, -1);
    }
}

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

    const gchar *username = gtk_entry_get_text(GTK_ENTRY(username_entry));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(password_entry));

    if (check_user(username) == 0)
    {
        gchar *alert_warning = g_strdup_printf("User tidak ditemukan");
        gtk_label_set_text(GTK_LABEL(banner_label), alert_warning);
        g_free(alert_warning);

        gtk_widget_show_all(current_window);
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

        printf("[[log] Login %d try %d\n", hasil, try);
    }
}

void create_user(GtkWidget *widget, gpointer data)
{
    GtkWidget *current_window = GTK_WIDGET(data);
    gtk_widget_hide(current_window);

    const gchar *username = gtk_entry_get_text(GTK_ENTRY(username_entry));
    const gchar *name = gtk_entry_get_text(GTK_ENTRY(name_entry));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(password_entry));
    printf("size e user%d", strlen(username));
    printf("size e nama%d", strlen(name));
    printf("size e pass%d", strlen(password));
    g_print("Username: %s\n", username);
    g_print("Name: %s\n", name);
    g_print("Password: %s\n", password);
    if (strlen(username) == 0)
    {
        gchar *alert_block = g_strdup_printf("USERNAME WAJIB DIISI!!!");
        gtk_label_set_text(GTK_LABEL(banner_label), alert_block);
        g_free(alert_block);
        gtk_widget_show_all(customer_register_window);
    }
    else if (strlen(name) == 0)
    {
        gchar *alert_block = g_strdup_printf("NAMA WAJIB DIISI!!!");
        gtk_label_set_text(GTK_LABEL(banner_label), alert_block);
        g_free(alert_block);
        gtk_widget_show_all(customer_register_window);
    }
    else if (strlen(password) == 0)
    {
        gchar *alert_block = g_strdup_printf("PASSWORD WAJIB DIISI!!!");
        gtk_label_set_text(GTK_LABEL(banner_label), alert_block);
        g_free(alert_block);
        gtk_widget_show_all(customer_register_window);
    }
    else
    {

        int hasile = register_user(username, name, password);
        if (hasile == 0)
        {
            gchar *alert_block = g_strdup_printf("Berhasil register, silahkan login!");
            gtk_label_set_text(GTK_LABEL(banner_label), alert_block);
            g_free(alert_block);
            create_login_user_window(current_window);
        }
        else if (hasile == 1)
        {
            gchar *alert_block = g_strdup_printf("Username sudah digunakan");
            gtk_label_set_text(GTK_LABEL(banner_label), alert_block);
            g_free(alert_block);
            gtk_widget_show_all(customer_register_window);
        }
    }

    printf("User: %s, Pw: %s", username, password);

    // gtk_widget_show_all(customers_login_window);
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

void show_calendar(GtkWidget *button, gpointer data)
{
    GtkWidget *dialog, *calendar;
    GtkWindow *parent = GTK_WINDOW(data);

    dialog = gtk_dialog_new_with_buttons("Tanggal", parent, GTK_DIALOG_MODAL, "OK", GTK_RESPONSE_OK, "Cancel", GTK_RESPONSE_CANCEL, NULL);
    calendar = gtk_calendar_new();
    gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(dialog))), calendar, FALSE, FALSE, 0);
    gtk_widget_show_all(dialog);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_OK)
    {
        guint year, month, day;
        gtk_calendar_get_date(GTK_CALENDAR(calendar), &year, &month, &day);
        char date_str[11];
        // sprintf(date_str, "%02d/%02d/%04d", day, month + 1, year);
        sprintf(date_str, "%04d-%02d-%02d", year, month + 1, day);
        gtk_button_set_label(GTK_BUTTON(button), date_str);
    }

    gtk_widget_destroy(dialog);
}

void on_save_button_clicked(GtkWidget *button, gpointer data)
{
    const gchar *no_penerbangan = gtk_entry_get_text(GTK_ENTRY(no_penerbangan_pesawat_entry));
    const gchar *nama_asal = gtk_entry_get_text(GTK_ENTRY(nama_asal_entry));
    const gchar *nama_tujuan = gtk_entry_get_text(GTK_ENTRY(nama_tujuan_entry));
    const gchar *jadwal_berangkat = gtk_button_get_label(GTK_BUTTON(jadwal_keberangakatan_button));
    const gchar *jadwal_datang = gtk_button_get_label(GTK_BUTTON(jadwal_kedatangan_button));
    const gchar *harganya = gtk_entry_get_text(GTK_ENTRY(harga_entry));
    gint jam_berangkat = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jam_keberangkatan));
    gint menit_berangkat = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(menit_keberangkatan));
    gint jam_kedatangannya = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jam_kedatangan));
    gint menit_kedatangannya = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(menit_kedatangan));
    g_print("value ne %s\t\t\tiki\n", no_penerbangan);
    char jam_keberangkatan[100];
    sprintf(jam_keberangkatan, "%02d:%02d:00", jam_berangkat, menit_berangkat);
    char jam_datang[100];
    sprintf(jam_datang, "%02d:%02d:00", jam_kedatangannya, menit_kedatangannya);
    printf("nilai ne %d\t\n", strlen(jam_keberangkatan));
    if (strlen(no_penerbangan) == 0)
    {
        gchar *alert_block = g_strdup_printf("no penerbangan kosong");
        gtk_label_set_text(GTK_LABEL(alert_warningin), alert_block);
        g_free(alert_block);
    }
    else if (strlen(entry_maskapai) == 0)
    {
        gchar *alert_block = g_strdup_printf("Nama maskapai kosong");
        gtk_label_set_text(GTK_LABEL(alert_warningin), alert_block);
        g_free(alert_block);
    }
    else if (strlen(entry_kelas) == 0)
    {
        gchar *alert_block = g_strdup_printf("Kelas penumpang kosong");
        gtk_label_set_text(GTK_LABEL(alert_warningin), alert_block);
        g_free(alert_block);
    }
    else if (strlen(nama_asal) == 0)
    {
        gchar *alert_block = g_strdup_printf("keberangkatan kosong");
        gtk_label_set_text(GTK_LABEL(alert_warningin), alert_block);
        g_free(alert_block);
    }
    else if (strlen(nama_tujuan) == 0)
    {
        gchar *alert_block = g_strdup_printf("kedatangan kosong");
        gtk_label_set_text(GTK_LABEL(alert_warningin), alert_block);
        g_free(alert_block);
    }
    else if (strlen(jadwal_berangkat) == 26)
    {
        gchar *alert_block = g_strdup_printf("jadwal keberangkatan kosong");
        gtk_label_set_text(GTK_LABEL(alert_warningin), alert_block);
        g_free(alert_block);
    }
    else if (strlen(jadwal_datang) == 0)
    {
        gchar *alert_block = g_strdup_printf("jadwal kedatangan kosong");
        gtk_label_set_text(GTK_LABEL(alert_warningin), alert_block);
        g_free(alert_block);
    }
    else if (strlen(harganya) == 0)
    {
        gchar *alert_block = g_strdup_printf("harganya kosong");
        gtk_label_set_text(GTK_LABEL(alert_warningin), alert_block);
        g_free(alert_block);
    }
    else
    {
        insert_flight_data(no_penerbangan, entry_maskapai, entry_kelas, nama_asal, nama_tujuan, jadwal_berangkat, jam_keberangkatan, jadwal_datang, jam_datang, harganya);
        g_print("suksess");
    }
}

GtkWidget *create_input_data_page(GtkWidget *parent_window)
{

    GtkWidget *nama_maskapai_mark;
    GtkWidget *nama_kelas_mark;
    GtkWidget *kelas_mark;
    GtkCellRenderer *renderer_kelas;
    GtkCellRenderer *renderer_maskapai;
    GtkTreeIter list_kelas;
    GtkTreeIter list_maskapai;
    GtkListStore *nama_maskapai_entry;

    GtkWidget *data_input = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    GtkWidget *no_penerbangan_pesawat_label = gtk_label_new("No Penerbangan");
    GtkWidget *nama_maskapai_label = gtk_label_new("Nama Maskapai");
    GtkWidget *nama_kelas_label = gtk_label_new("Jenis Kelas Pesawat");
    GtkWidget *nama_asal_label = gtk_label_new("Asal Keberangkatan Pesawat ");
    GtkWidget *nama_tujuan_label = gtk_label_new("Tujuan Kedatangan Pesawat ");
    GtkWidget *nama_harga_label = gtk_label_new("Harga");

    no_penerbangan_pesawat_entry = gtk_entry_new();
    nama_maskapai_entry = gtk_list_store_new(1, G_TYPE_STRING);
    nama_asal_entry = gtk_entry_new();
    nama_tujuan_entry = gtk_entry_new();
    harga_entry = gtk_entry_new();

    gtk_list_store_append(nama_maskapai_entry, &list_maskapai);
    gtk_list_store_set(nama_maskapai_entry, &list_maskapai, 0, "Pilih Maskapai", -1);
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
    gtk_list_store_set(kelas_entry, &list_kelas, 0, "Pilih Kelas", -1);
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
    jadwal_keberangakatan_button = gtk_button_new_with_label("Pilih Tanggal");
    g_signal_connect(jadwal_keberangakatan_button, "clicked", G_CALLBACK(show_calendar), parent_window);

    GtkWidget *jam_keberangakatan_label = gtk_label_new("Jam Penerbangan:");
    jam_keberangkatan = gtk_spin_button_new_with_range(0, 23, 1);
    menit_keberangkatan = gtk_spin_button_new_with_range(0, 59, 1);

    GtkWidget *jadwal_kedatangan_label = gtk_label_new("Jadwal Kedatangan:");
    jadwal_kedatangan_button = gtk_button_new_with_label("Pilih Tanggal");
    g_signal_connect(jadwal_kedatangan_button, "clicked", G_CALLBACK(show_calendar), parent_window);

    GtkWidget *jam_kedatangan_label = gtk_label_new("Jam Kedatangan:");
    jam_kedatangan = gtk_spin_button_new_with_range(0, 23, 1);
    menit_kedatangan = gtk_spin_button_new_with_range(0, 59, 1);

    GtkWidget *save_button = gtk_button_new_with_label("Simpan");
    g_signal_connect(save_button, "clicked", G_CALLBACK(on_save_button_clicked), parent_window);
    GtkWidget *waktu_keberangakatan = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    GtkWidget *waktu_kedatangan = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    alert_warningin = gtk_label_new(NULL);
    PangoAttrList *attr_list = pango_attr_list_new();
    PangoAttribute *attr_size = pango_attr_size_new_absolute(30 * PANGO_SCALE);
    pango_attr_list_insert(attr_list, attr_size);
    gtk_label_set_attributes(GTK_LABEL(alert_warningin), attr_list);
    pango_attr_list_unref(attr_list);
    gtk_box_pack_start(GTK_BOX(data_input), alert_warningin, FALSE, FALSE, 5);
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
    gtk_box_pack_start(GTK_BOX(waktu_keberangakatan), jam_keberangkatan, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(waktu_keberangakatan), menit_keberangkatan, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(data_input), jadwal_kedatangan_label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(data_input), jadwal_kedatangan_button, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(data_input), jam_kedatangan_label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(data_input), waktu_kedatangan, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(waktu_kedatangan), jam_kedatangan, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(waktu_kedatangan), menit_kedatangan, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(data_input), nama_harga_label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(data_input), harga_entry, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(data_input), save_button, FALSE, FALSE, 5);
    g_signal_connect(nama_maskapai_mark, "changed", G_CALLBACK(maskapai_list), NULL);
    g_signal_connect(nama_kelas_mark, "changed", G_CALLBACK(kelas_list), NULL);

    return data_input;
}

void on_selection_changed(GtkTreeSelection *selection, gpointer data)
{
    current_selection = selection;
}

void on_checkout_clicked(GtkWidget *widget, gpointer data)
{
    GtkWidget *current_window = GTK_WIDGET(data);
    gtk_widget_hide(current_window);

    tickets_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(tickets_window), "Welcome Window");
    gtk_window_set_default_size(GTK_WINDOW(tickets_window), 500, 500);
    gtk_container_set_border_width(GTK_CONTAINER(tickets_window), 10);
    // GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(tickets_window), vbox);

    char notif_order[256];
    sprintf(notif_order, "Silahkan Cetak Tiket Anda!");
    banner_label = gtk_label_new(NULL);
    gtk_label_set_text(GTK_LABEL(banner_label), notif_order);
    PangoAttrList *attr_list = pango_attr_list_new();
    PangoAttribute *attr_size = pango_attr_size_new_absolute(20 * PANGO_SCALE);
    pango_attr_list_insert(attr_list, attr_size);
    gtk_label_set_attributes(GTK_LABEL(banner_label), attr_list);
    pango_attr_list_unref(attr_list);

    GtkWidget *image = gtk_image_new_from_file("assets/tickes.jpg");

    char detail_tiket[256];
    GtkWidget *ticket_label;
    sprintf(detail_tiket, "A/n: %s", current_user.name);
    ticket_label = gtk_label_new(NULL);
    gtk_label_set_text(GTK_LABEL(ticket_label), detail_tiket);

    PangoAttrList *attr_list2 = pango_attr_list_new();
    PangoAttribute *attr_size2 = pango_attr_size_new_absolute(20 * PANGO_SCALE);
    pango_attr_list_insert(attr_list2, attr_size2);
    gtk_label_set_attributes(GTK_LABEL(ticket_label), attr_list2);
    pango_attr_list_unref(attr_list2);

    gtk_box_pack_start(GTK_BOX(vbox), banner_label, FALSE, FALSE, 0);
    // gtk_box_pack_start(GTK_BOX(vbox), detail_tiket, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), image, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), ticket_label, FALSE, FALSE, 0);
    // gtk_box_pack_start(GTK_BOX(vbox), button_checkout, FALSE, FALSE, 0);
    gtk_widget_show_all(tickets_window);
}

void on_button_clicked(GtkButton *button, gpointer data)
{
    // GtkWidget *orderwindow;

    orders_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(orders_window), "Welcome Window");
    gtk_window_set_default_size(GTK_WINDOW(orders_window), 500, 500);
    gtk_container_set_border_width(GTK_CONTAINER(orders_window), 10);
    // GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(orders_window), vbox);

    char notif_order[256];
    sprintf(notif_order, "Silahkan melakukan pembayaran!");
    banner_label = gtk_label_new(NULL);
    gtk_label_set_text(GTK_LABEL(banner_label), notif_order);
    PangoAttrList *attr_list = pango_attr_list_new();
    PangoAttribute *attr_size = pango_attr_size_new_absolute(20 * PANGO_SCALE);
    pango_attr_list_insert(attr_list, attr_size);
    gtk_label_set_attributes(GTK_LABEL(banner_label), attr_list);
    pango_attr_list_unref(attr_list);

    GtkWidget *image = gtk_image_new_from_file("assets/qr.png");

    GtkWidget *button_checkout = gtk_button_new_with_label("CHECKOUT");
    g_signal_connect(button_checkout, "clicked", G_CALLBACK(on_checkout_clicked), orders_window);

    if (current_selection == NULL)
    {
        // No selection made
        g_print("No row selected.\n");
        return;
    }

    GtkTreeModel *model;
    GtkTreeIter iter;
    if (gtk_tree_selection_get_selected(current_selection, &model, &iter))
    {
        gchar *no_penerbangan;
        gchar *maskapai;
        gchar *kelas;
        gchar *asal;
        gchar *tujuan;
        gchar *tgl_berangkat;
        gchar *waktu_keberangkatan;
        gchar *tgl_datang;
        gchar *waktu_kedatangan;
        guint harga;

        gtk_tree_model_get(model, &iter,
                           FILE_NAME, &no_penerbangan,
                           FILE_MASKAPAI, &maskapai,
                           FILE_KELAS, &kelas,
                           FILE_ASAL, &asal,
                           FILE_TUJUAN, &tujuan,
                           FILE_TGL_BERANGKAT, &tgl_berangkat,
                           FILE_WAKTU_B, &waktu_keberangkatan,
                           FILE_TGL_DATANG, &tgl_datang,
                           FILE_WAKTU_T, &waktu_kedatangan,
                           FILE_HARGA, &harga,
                           -1);

        // Use the data (e.g., print it or pass it to another function)
        g_print("No Penerbangan: %s\n", no_penerbangan);
        g_print("Maskapai: %s\n", maskapai);
        g_print("Kelas: %s\n", kelas);
        g_print("Asal: %s\n", asal);
        g_print("Tujuan: %s\n", tujuan);
        g_print("Tanggal Berangkat: %s\n", tgl_berangkat);
        g_print("Waktu Keberangkatan: %s\n", waktu_keberangkatan);
        g_print("Tanggal Datang: %s\n", tgl_datang);
        g_print("Waktu Kedatangan: %s\n", waktu_kedatangan);
        g_print("Harga: %u\n", harga);

        // g_free(no_penerbangan);
        g_free(maskapai);
        g_free(kelas);
        g_free(asal);
        g_free(tujuan);
        g_free(tgl_berangkat);
        g_free(waktu_keberangkatan);
        g_free(tgl_datang);
        g_free(waktu_kedatangan);

        char nomor_penerbangan[256];
        sprintf(nomor_penerbangan, "%s", no_penerbangan);

        create_ticket(current_user.name, nomor_penerbangan);
        create_orders(current_user.name);
    }

    gtk_box_pack_start(GTK_BOX(vbox), banner_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), image, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button_checkout, FALSE, FALSE, 0);
    gtk_widget_show_all(orders_window);
}

void on_row_activated(GtkTreeView *tree_view, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data)
{
    GtkTreeModel *model = (GtkTreeModel *)user_data;
    GtkTreeIter iter;

    if (gtk_tree_model_get_iter(model, &iter, path))
    {
        gchar *no_penerbangan;
        gchar *maskapai;
        gchar *kelas;
        gchar *asal;
        gchar *tujuan;
        gchar *tgl_berangkat;
        gchar *waktu_keberangkatan;
        gchar *tgl_datang;
        gchar *waktu_kedatangan;
        guint harga;

        gtk_tree_model_get(model, &iter,
                           FILE_NAME, &no_penerbangan,
                           FILE_MASKAPAI, &maskapai,
                           FILE_KELAS, &kelas,
                           FILE_ASAL, &asal,
                           FILE_TUJUAN, &tujuan,
                           FILE_TGL_BERANGKAT, &tgl_berangkat,
                           FILE_WAKTU_B, &waktu_keberangkatan,
                           FILE_TGL_DATANG, &tgl_datang,
                           FILE_WAKTU_T, &waktu_kedatangan,
                           FILE_HARGA, &harga,
                           -1);

        // Tampilkan atau gunakan data yang diambil
        g_print("No Penerbangan: %s\n", no_penerbangan);
        g_print("Maskapai: %s\n", maskapai);
        g_print("Kelas: %s\n", kelas);
        g_print("Asal: %s\n", asal);
        g_print("Tujuan: %s\n", tujuan);
        g_print("Tanggal Berangkat: %s\n", tgl_berangkat);
        g_print("Waktu Keberangkatan: %s\n", waktu_keberangkatan);
        g_print("Tanggal Kedatangan: %s\n", tgl_datang);
        g_print("Waktu Kedatangan: %s\n", waktu_kedatangan);
        g_print("Harga: %u\n", harga);

        // Jangan lupa untuk membebaskan memori yang dialokasikan oleh gtk_tree_model_get
        g_free(no_penerbangan);
        g_free(maskapai);
        g_free(kelas);
        g_free(asal);
        g_free(tujuan);
        g_free(tgl_berangkat);
        g_free(waktu_keberangkatan);
        g_free(tgl_datang);
        g_free(waktu_kedatangan);
    }
}

GtkWidget *show_pembelian_data(GtkWidget *parent_windows)
{
    GtkTreeIter iter;
    GtkListStore *model;
    GtkWidget *view;
    GtkTreeViewColumn *column;
    GtkWidget *show_history_page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    model = gtk_list_store_new(N_COLUMNS,
                               G_TYPE_STRING,
                               G_TYPE_STRING,
                               G_TYPE_STRING,
                               G_TYPE_STRING,
                               G_TYPE_STRING,
                               G_TYPE_STRING,
                               G_TYPE_STRING,
                               G_TYPE_STRING,
                               G_TYPE_STRING,
                               G_TYPE_UINT,
                               G_TYPE_UINT,
                               G_TYPE_STRING,
                               G_TYPE_STRING);

    int num_rows = get_jumlah_penerbangan();
    printf("%d", num_rows);
    FlightDetails flight_details[num_rows];

    int res = get_data_penerbangan(flight_details);

    for (int i = 0; i < num_rows; i++)
    {
        gtk_list_store_insert_with_values(model, NULL, -1,
                                          FILE_NAME, flight_details[i].no_penerbangan,
                                          FILE_MASKAPAI, flight_details[i].maskapai,
                                          FILE_KELAS, flight_details[i].kelas,
                                          FILE_ASAL, flight_details[i].asal,
                                          FILE_TUJUAN, flight_details[i].tujuan,
                                          FILE_TGL_BERANGKAT, flight_details[i].tgl_berangkat,
                                          FILE_WAKTU_B, flight_details[i].waktu_keberangkatan,
                                          FILE_TGL_DATANG, flight_details[i].tgl_datang,
                                          FILE_WAKTU_T, flight_details[i].waktu_kedatangan,
                                          FILE_HARGA, flight_details[i].harga,
                                          -1);
    }

    /* VIEW */
    view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(model));

    g_object_unref(model);
    column = gtk_tree_view_column_new_with_attributes("No Penerbangan",
                                                      gtk_cell_renderer_text_new(),
                                                      "text", FILE_NAME,
                                                      "background", COLOR,
                                                      NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("Maskapai",
                                                      gtk_cell_renderer_text_new(),
                                                      "text", FILE_MASKAPAI,
                                                      "background", COLOR,
                                                      NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("Kelas",
                                                      gtk_cell_renderer_text_new(),
                                                      "text", FILE_KELAS,
                                                      "background", COLOR,
                                                      NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("Asal Keberangkatan",
                                                      gtk_cell_renderer_text_new(),
                                                      "text", FILE_ASAL,
                                                      "background", COLOR,
                                                      NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("Tujuan ",
                                                      gtk_cell_renderer_text_new(),
                                                      "text", FILE_TUJUAN,
                                                      "background", COLOR,
                                                      NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);
    column = gtk_tree_view_column_new_with_attributes("Tanggal Berangkat",
                                                      gtk_cell_renderer_text_new(),
                                                      "text", FILE_TGL_BERANGKAT,
                                                      "background", COLOR,
                                                      NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);
    column = gtk_tree_view_column_new_with_attributes("Waktu keberangkatan",
                                                      gtk_cell_renderer_text_new(),
                                                      "text", FILE_WAKTU_B,
                                                      "background", COLOR,
                                                      NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);
    column = gtk_tree_view_column_new_with_attributes("Tanggal kedatangan",
                                                      gtk_cell_renderer_text_new(),
                                                      "text", FILE_TGL_DATANG,
                                                      "background", COLOR,
                                                      NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("Waktu kedatangan",
                                                      gtk_cell_renderer_text_new(),
                                                      "text", FILE_WAKTU_T,
                                                      "background", COLOR,
                                                      NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("Harga Tiket Pesawat",
                                                      gtk_cell_renderer_text_new(),
                                                      "text", FILE_HARGA,
                                                      "background", COLOR,
                                                      NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    GtkWidget *button;
    button = gtk_button_new_with_label("BELI TIKET");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);

    GtkTreeSelection *selection;
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(view));
    g_signal_connect(selection, "changed", G_CALLBACK(on_selection_changed), NULL);

    GtkWidget *scrollview = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scrollview), view);
    // gtk_container_add(GTK_CONTAINER(scrollview), view);
    gtk_widget_set_hexpand(scrollview, TRUE);
    gtk_widget_set_vexpand(scrollview, TRUE);
    gtk_container_add(GTK_CONTAINER(show_history_page), scrollview);
    gtk_container_add(GTK_CONTAINER(show_history_page), button);

    return show_history_page;
}

GtkWidget *show_history_data(GtkWidget *parent_windows)
{
    GtkListStore *model;
    GtkWidget *view;
    GtkTreeViewColumn *column;
    GtkWidget *show_history_page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    model = gtk_list_store_new(N_COLUMNS,
                               G_TYPE_STRING,
                               G_TYPE_STRING,
                               G_TYPE_STRING,
                               G_TYPE_STRING,
                               G_TYPE_STRING,
                               G_TYPE_STRING,
                               G_TYPE_STRING,
                               G_TYPE_STRING,
                               G_TYPE_STRING,
                               G_TYPE_UINT,
                               G_TYPE_UINT,
                               G_TYPE_STRING,
                               G_TYPE_STRING);

    int num_rows = get_jumlah_penerbangan();
    printf("%d", num_rows);
    FlightDetails flight_details[num_rows];

    int res = get_data_penerbangan(flight_details);

    for (int i = 0; i < num_rows; i++)
    {
        gtk_list_store_insert_with_values(model, NULL, -1,
                                          FILE_NAME, flight_details[i].no_penerbangan,
                                          FILE_MASKAPAI, flight_details[i].maskapai,
                                          FILE_KELAS, flight_details[i].kelas,
                                          FILE_ASAL, flight_details[i].asal,
                                          FILE_TUJUAN, flight_details[i].tujuan,
                                          FILE_TGL_BERANGKAT, flight_details[i].tgl_berangkat,
                                          FILE_WAKTU_B, flight_details[i].waktu_keberangkatan,
                                          FILE_TGL_DATANG, flight_details[i].tgl_datang,
                                          FILE_WAKTU_T, flight_details[i].waktu_kedatangan,
                                          FILE_HARGA, flight_details[i].harga,
                                          -1);
    }

    /* VIEW */
    view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(model));
    g_signal_connect(view, "row-activated", G_CALLBACK(on_row_activated), model);
    g_object_unref(model);
    column = gtk_tree_view_column_new_with_attributes("No Penerbangan",
                                                      gtk_cell_renderer_text_new(),
                                                      "text", FILE_NAME,
                                                      "background", COLOR,
                                                      NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("Maskapai",
                                                      gtk_cell_renderer_text_new(),
                                                      "text", FILE_MASKAPAI,
                                                      "background", COLOR,
                                                      NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("Kelas",
                                                      gtk_cell_renderer_text_new(),
                                                      "text", FILE_KELAS,
                                                      "background", COLOR,
                                                      NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("Asal Keberangkatan",
                                                      gtk_cell_renderer_text_new(),
                                                      "text", FILE_ASAL,
                                                      "background", COLOR,
                                                      NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("Tujuan ",
                                                      gtk_cell_renderer_text_new(),
                                                      "text", FILE_TUJUAN,
                                                      "background", COLOR,
                                                      NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);
    column = gtk_tree_view_column_new_with_attributes("Tanggal Berangkat",
                                                      gtk_cell_renderer_text_new(),
                                                      "text", FILE_TGL_BERANGKAT,
                                                      "background", COLOR,
                                                      NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);
    column = gtk_tree_view_column_new_with_attributes("Waktu keberangkatan",
                                                      gtk_cell_renderer_text_new(),
                                                      "text", FILE_WAKTU_B,
                                                      "background", COLOR,
                                                      NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);
    column = gtk_tree_view_column_new_with_attributes("Tanggal kedatangan",
                                                      gtk_cell_renderer_text_new(),
                                                      "text", FILE_TGL_DATANG,
                                                      "background", COLOR,
                                                      NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column =
        ("Waktu kedatangan",
         gtk_cell_renderer_text_new(),
         "text", FILE_WAKTU_T,
         "background", COLOR,
         NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    column = gtk_tree_view_column_new_with_attributes("Harga Tiket Peaswat",
                                                      gtk_cell_renderer_text_new(),
                                                      "text", FILE_HARGA,
                                                      "background", COLOR,
                                                      NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(view), column);

    GtkWidget *scrollview = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scrollview), view);
    gtk_widget_set_hexpand(scrollview, TRUE);
    gtk_widget_set_vexpand(scrollview, TRUE);
    gtk_container_add(GTK_CONTAINER(show_history_page), scrollview);

    return show_history_page;
}

void create_welcome_admin_window(GtkWidget *parent_window)
{
    gtk_widget_hide(parent_window);
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

    // FormData form_data;

    welcome_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(welcome_window), "Admin Panel");
    gtk_window_set_default_size(GTK_WINDOW(welcome_window), 1700, 800);
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

    char selamat_datang[256];
    sprintf(selamat_datang, "Selamat Datang Admin!");
    label = gtk_label_new(NULL);
    gtk_label_set_text(GTK_LABEL(label), selamat_datang);
    PangoAttrList *attr_list = pango_attr_list_new();
    PangoAttribute *attr_size = pango_attr_size_new_absolute(20 * PANGO_SCALE);
    pango_attr_list_insert(attr_list, attr_size);
    gtk_label_set_attributes(GTK_LABEL(label), attr_list);
    pango_attr_list_unref(attr_list);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    hdata_history = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    hdata_input = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    data_input = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    data_history = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);

    GtkWidget *image = gtk_image_new_from_file("assets/banner2.png");
    gtk_box_pack_start(GTK_BOX(vbox), image, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

    gtk_stack_add_named(GTK_STACK(stack), vbox, "home");
    GtkWidget *input_data_page = create_input_data_page(welcome_window);
    GtkWidget *history_data_page = show_history_data(welcome_window);

    gtk_stack_add_titled(GTK_STACK(stack), input_data_page, "inputdata", "Input Data Penerbangan");

    gtk_stack_add_titled(GTK_STACK(stack), history_data_page, "historydata", "Data Penerbangan");

    g_signal_connect(welcome_window, "destroy", G_CALLBACK(destroy), NULL);
    gtk_widget_show_all(welcome_window);
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
    gtk_window_set_default_size(GTK_WINDOW(welcome_window), 1700, 900);
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
    char selamat_datang[256];
    sprintf(selamat_datang, "Selamat datang, %s!", current_user.name);
    label = gtk_label_new(NULL);
    gtk_label_set_text(GTK_LABEL(label), selamat_datang);
    PangoAttrList *attr_list = pango_attr_list_new();
    PangoAttribute *attr_size = pango_attr_size_new_absolute(30 * PANGO_SCALE);
    PangoAttribute *attr_style = pango_attr_weight_new(PANGO_WEIGHT_BOLD);
    pango_attr_list_insert(attr_list, attr_size);
    pango_attr_list_insert(attr_list, attr_size);
    gtk_label_set_attributes(GTK_LABEL(label), attr_list);
    pango_attr_list_unref(attr_list);
    GtkWidget *tanggalan = gtk_calendar_new();
    GtkWidget *image = gtk_image_new_from_file("assets/banner2.png");
    gtk_box_pack_start(GTK_BOX(grid), image, TRUE, TRUE, 0);
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *welcom = gtk_label_new("Welcome!");

    vbox2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_pack_start(GTK_BOX(vbox2), image, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox2), label, TRUE, TRUE, 0);
    // gtk_box_pack_start(GTK_BOX(vbox2), tanggalan, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(vbox), banner_label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), welcom, TRUE, TRUE, 0);
    gtk_stack_add_named(GTK_STACK(stack), vbox2, "home");

    penjualan_button = gtk_button_new_with_label("Riwayat Pembelian akan muncul disini");
    g_signal_connect(G_OBJECT(penjualan_button), "clicked", G_CALLBACK(show_penjualan), NULL);

    history_penjualan_button = gtk_button_new_with_label("History");
    g_signal_connect(G_OBJECT(history_penjualan_button), "clicked", G_CALLBACK(show_history_penjualan), NULL);

    GtkWidget *input_data_page = show_pembelian_data(welcome_window);

    gtk_stack_add_titled(GTK_STACK(stack), input_data_page, "order", "Beli Tiket");

    gtk_stack_add_titled(GTK_STACK(stack), penjualan_button, "history", "Riwayat Pembelian");

    g_signal_connect(welcome_window, "destroy", G_CALLBACK(destroy), NULL);
    gtk_widget_show_all(welcome_window);
}

void destroy(GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}
