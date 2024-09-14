/**
 * compile: gcc -o gtk gtk.c `pkg-config --cflags --libs gtk+-3.0`
 */

#include <gtk/gtk.h>
#include <stdio.h>

static void on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
    // Check for Shift + Alt + E
    printf("Integer as string: %i : %i : %i : %i\n", ((event->state & GDK_SHIFT_MASK) == 1), ((event->state & GDK_MOD1_MASK) == 8), event->keyval , GDK_KEY_R);
    if ((event->state & GDK_SHIFT_MASK) && (event->state & GDK_MOD1_MASK) && (event->keyval == GDK_KEY_R)) {
        g_print("Shift + Alt + R pressed!\n");
        // Execute your command here
        system("notify-send key pressed");  // Replace with your command
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Create a new window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Key Grab Example");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Connect the key press event
    g_signal_connect(window, "key-press-event", G_CALLBACK(on_key_press), NULL);

    // Show the window
    gtk_widget_show_all(window);

    // Connect the destroy event to quit the application
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Start the GTK main loop
    gtk_main();

    return 0;
}
