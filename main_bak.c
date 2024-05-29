int main(int argc, char *argv[])
{
    if ((connect_mysql()) == 0)
    {
        printf("sukses");
    }
    GtkWidget *vbox;
    GtkWidget *username_label;
    GtkWidget *password_label;
    GtkWidget *login_button;
    GtkWidget *image;
    GtkWidget *banner_label;

    gtk_init(&argc, &argv);
    login_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    g_signal_connect(login_window, "destroy", G_CALLBACK(destroy), NULL);

    gtk_container_set_border_width(GTK_CONTAINER(login_window), WINDOW_SIZE);

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
    g_signal_connect(G_OBJECT(login_button), "clicked", G_CALLBACK(loginin), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), login_button, TRUE, TRUE, 0);

    gtk_widget_show_all(login_window);
    gtk_main();

    return 0;
}