#include <gtk/gtk.h>

void cb_combo_change(GtkComboBox *combo, gpointer user_data)
{
    gint index = gtk_combo_box_get_active(combo);
    if (index)
    { // we need some string to be displayed
        GtkTreeModel *model;
        GtkTreeIter iter;
        gchar *buf;
        model = gtk_combo_box_get_model(combo);
        gtk_tree_model_iter_nth_child(model, &iter, NULL, index);
        gtk_tree_model_get(model, &iter, 0, &buf, -1);
        g_print("%s\n", buf);
        g_free(buf);
    }
}

void show_message_cb(GtkMenuItem *item, gpointer user_data)
{
    g_print("Hello world\n");
}

int main(int argc, char *argv[])
{
    GtkWidget *toplevel;
    GtkWidget *center_vbox;
    GtkWidget *menuBar;
    GtkWidget *menuItem1;
    GtkWidget *submenu1;
    GtkWidget *item_message;
    GtkWidget *item_quit;
    GtkWidget *combobox;
    GtkListStore *combo_ls;
    GtkCellRenderer *renderer;
    GtkTreeIter iter;
    gtk_init(&argc, &argv);
    /* create toplevel window */
    toplevel = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    /* create the box here */
    center_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    /* create menubar */
    menuBar = gtk_menu_bar_new();
    /* create 1st menu item */
    menuItem1 = gtk_menu_item_new_with_mnemonic("_Application");
    /* add the submenu for the 1st menu item */
    submenu1 = gtk_menu_new();
    /* add the message item */
    item_message = gtk_menu_item_new_with_label("Message");
    /* add the quit item menu for the submenu */
    item_quit = gtk_menu_item_new_with_label("Quit");
    /* create the list model for the combo */
    combo_ls = gtk_list_store_new(1, G_TYPE_STRING);
    /* add some strings */
    gtk_list_store_append(combo_ls, &iter);
    gtk_list_store_set(combo_ls, &iter, 0, "Choose one", -1);
    gtk_list_store_append(combo_ls, &iter);
    gtk_list_store_set(combo_ls, &iter, 0, "String1", -1);
    gtk_list_store_append(combo_ls, &iter);
    gtk_list_store_set(combo_ls, &iter, 0, "String2", -1);
    /* add a combobox with the model
     * you could use combo_box_text for faster text append */
    combobox = gtk_combo_box_new_with_model(GTK_TREE_MODEL(combo_ls));
    /* destroy here the model, because you increase its reference
     * by attach it to the combo */
    g_object_unref(combo_ls);
    /* now prepare the combo */
    renderer = gtk_cell_renderer_text_new();
    gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(combobox), renderer, TRUE);
    gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(combobox), renderer, "text", 0, NULL);
    /* set index to 0 */
    gtk_combo_box_set_active(GTK_COMBO_BOX(combobox), 0);
    /* packing */
    gtk_menu_shell_append(GTK_MENU_SHELL(submenu1), item_message);
    gtk_menu_shell_append(GTK_MENU_SHELL(submenu1), item_quit);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuItem1), submenu1);
    gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), menuItem1);
    gtk_box_pack_start(GTK_BOX(center_vbox), menuBar, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(center_vbox), combobox, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(toplevel), center_vbox);
    /* signal handlers */
    g_signal_connect(toplevel, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(combobox, "changed", G_CALLBACK(cb_combo_change), NULL);
    g_signal_connect_swapped(item_quit, "activate", G_CALLBACK(gtk_widget_destroy), toplevel);
    g_signal_connect(item_message, "activate", G_CALLBACK(show_message_cb), NULL);
    /* let them loose */
    gtk_widget_show_all(toplevel);
    gtk_main();
    return 0;
}