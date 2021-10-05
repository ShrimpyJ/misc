/* Compile with
   gcc `pkg-config --cflags gtk+-3.0' gtk.c -o gtk `pkg-config --libs gtk+-3.0`
*/

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#define DEFAULT_H     800
#define DEFAULT_W     600
#define DEFAULT_NAME  "Window"

static void button_print(GtkWidget *widget, gpointer data)
{
	g_print("Hello World\n");
}

static void activate(GtkWidget *app, gpointer data)
{
	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *button_box;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), DEFAULT_NAME);
	gtk_window_set_default_size(GTK_WINDOW(window), DEFAULT_H, DEFAULT_W);

	button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_container_add(GTK_CONTAINER(window), button_box);

	button = gtk_button_new_with_label("Click me");
	g_signal_connect(button, "clicked", G_CALLBACK(button_print), NULL);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
	gtk_container_add(GTK_CONTAINER(button_box), button);

	gtk_widget_show_all(window);
}

int main(int argc, char** argv)
{
	GtkApplication *app;
	int status;

	app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return status;
}
