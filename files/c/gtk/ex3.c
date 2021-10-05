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

int main(int argc, char** argv)
{
	GtkBuilder *builder;
	GObject *window;
	GObject *button;
	GError *error = NULL;

	gtk_init(&argc, &argv);

	builder = gtk_builder_new();
	if (gtk_builder_add_from_file(builder, "builder.ui", &error) == 0){
		g_printerr("Error loading file %s\n", error->message);
		g_clear_error(&error);
		exit(1);
	}

	window = gtk_builder_get_object(builder, "window");
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	button - gtk_builder_get_object(builder, "button1");
	g_signal_connect(button, "clicked", G_CALLBACK(button_print), NULL);

	button - gtk_builder_get_object(builder, "button2");
	g_signal_connect(button, "clicked", G_CALLBACK(button_print), NULL);

	button - gtk_builder_get_object(builder, "quit");
	g_signal_connect(button, "clicked", G_CALLBACK(gtk_main_quit), NULL);

	gtk_main();

	return 0;
}
