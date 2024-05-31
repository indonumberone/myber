#include <stdio.h>
#include <gtk/gtk.h>

struct windows
{
    GtkWidget *window[2];
    int current;
};

static void hide_wind(GtkButton *dummy, gpointer wins);

gboolean destroy(GtkWidget *window);

int main(int argc, char *argv[])
{
    GtkWidget *window, *button, *box;
    struct windows windows;
    char *title, *caption;
    int i;

    gtk_init(&argc, &argv);
    for (i = 0; i < 2; i++)
    {
        windows.current = i;
        windows.window[i] = window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        title = i == 0 ? "Window A" : "Window B";
        gtk_window_set_title(GTK_WINDOW(window), title);
        gtk_container_set_border_width(GTK_CONTAINER(window), 10);
        gtk_widget_set_size_request(window, 300, 300);
        gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
        caption = i == 0 ? "Goto Window B" : "Goto Window A";
        button = gtk_button_new_with_label(caption);
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(hide_wind), &windows);
        box = gtk_box_new(TRUE, 1);
        gtk_box_pack_end(GTK_BOX(box), button, TRUE, TRUE, 1);
        gtk_container_add(GTK_CONTAINER(window), box);
    }
    windows.current = 0;
    gtk_widget_show_all(windows.window[0]);
    gtk_main();
    return 0;
}

static void hide_wind(GtkButton *dummy, gpointer wins)
{
    struct windows *windows = wins;

    (void)dummy;
    gtk_widget_hide(windows->window[windows->current]);
    windows->current = !windows->current;
    gtk_widget_show_all(windows->window[windows->current]);
}

gboolean destroy(GtkWidget *widget)
{
    gtk_widget_destroy(widget);
    return TRUE;
}