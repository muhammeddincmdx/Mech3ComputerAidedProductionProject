#include <gtk/gtk.h>
#include <wiringPi.h>
#define signalPin 29

GtkWidget *window;
GtkWidget *toggleButton;
GtkWidget *label;

void toggle_button_callback(GtkWidget *widget, gpointer data) {
    static int signalState = 0;
    signalState = !signalState;
    digitalWrite(signalPin, signalState);
    gtk_label_set_text(GTK_LABEL(label), signalState ? "Piston Açık" : "Piston Kapalı");
    GdkRGBA color;
    gdk_rgba_parse(&color, signalState ? "#2ecc71" : "#c0392b"); 
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &color);
    #pragma GCC diagnostic pop
}
int main(int argc, char *argv[]) {
    wiringPiSetup();
    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Piston Kontrol Projesi");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 250);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); 
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    GtkWidget *title1 = gtk_label_new("Computer Aided Design and Production");
    GtkWidget *title2 = gtk_label_new("Piston Kontrol Projesi");
    GtkWidget *title3 = gtk_label_new("Muhammed DİNÇ & Ahmet CAN");
    gtk_label_set_xalign(GTK_LABEL(title1), 0.5); 
    gtk_label_set_xalign(GTK_LABEL(title2), 0.5); 
    gtk_label_set_xalign(GTK_LABEL(title3), 0.5); 
    gtk_box_pack_start(GTK_BOX(vbox), title1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), title2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), title3, TRUE, TRUE, 0);
    gtk_box_set_spacing(GTK_BOX(vbox), 10);
    label = gtk_label_new("Piston Kapalı");
    gtk_label_set_xalign(GTK_LABEL(label), 0.5); 
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);
    toggleButton = gtk_toggle_button_new_with_label("Pistonu Aç/Kapat");
    gtk_widget_set_size_request(toggleButton, 150, 30); 
    g_signal_connect(toggleButton, "toggled", G_CALLBACK(toggle_button_callback), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), toggleButton, TRUE, TRUE, 0);S
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
        "window {"
        "   background-color: #000000;" 
        "}"
        "label {"
        "   color: #fff;" 
        "}"
        "button {"
        "   background-color: #3498db;" 
        "   border-radius: 10px;" 
        "   padding: 10px 20px;" 
        "   color: #fff;" 
        "}"
        "button:hover {"
        "   background-color: #2980b9;" 
        "}", -1, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    g_object_unref(provider);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}

