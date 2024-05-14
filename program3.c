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

    // Label'in rengini değiştir
    GdkRGBA color;
    gdk_rgba_parse(&color, signalState ? "#2ecc71" : "#c0392b"); // Yeşil veya kırmızı renk

    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    gtk_widget_override_background_color(label, GTK_STATE_FLAG_NORMAL, &color);
    #pragma GCC diagnostic pop
}

int main(int argc, char *argv[]) {
    // WiringPi'yi başlat
    wiringPiSetup();

    // GTK'yi başlat
    gtk_init(&argc, &argv);

    // Pencere oluştur
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Piston Kontrol Projesi");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 250); // Ölçüler burada belirleniyor
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); // Pencereyi ekranda ortala

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Dikey bir kutu oluştur
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Başlıkları ekleyin
    GtkWidget *title1 = gtk_label_new("Computer Aided Design and Production");
    GtkWidget *title2 = gtk_label_new("Piston Kontrol Projesi");
    GtkWidget *title3 = gtk_label_new("Muhammed DİNÇ & Ahmet CAN");
    gtk_label_set_xalign(GTK_LABEL(title1), 0.5); // X ekseninde ortalanma
    gtk_label_set_xalign(GTK_LABEL(title2), 0.5); // X ekseninde ortalanma
    gtk_label_set_xalign(GTK_LABEL(title3), 0.5); // X ekseninde ortalanma
    gtk_box_pack_start(GTK_BOX(vbox), title1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), title2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), title3, TRUE, TRUE, 0);
    gtk_box_set_spacing(GTK_BOX(vbox), 10);

    // Piston durumu etiketi oluştur
    label = gtk_label_new("Piston Kapalı");
    gtk_label_set_xalign(GTK_LABEL(label), 0.5); // X ekseninde ortalanma
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);

    // Toggle button oluştur
    toggleButton = gtk_toggle_button_new_with_label("Pistonu Aç/Kapat");
    gtk_widget_set_size_request(toggleButton, 150, 30); // Butonun boyutunu ayarla
    g_signal_connect(toggleButton, "toggled", G_CALLBACK(toggle_button_callback), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), toggleButton, TRUE, TRUE, 0);

    // CSS provider'ı oluştur
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
        "window {"
        "   background-color: #000000;" /* Pencere arka plan rengi */
        "}"
        "label {"
        "   color: #fff;" /* Metin rengi */
        "}"
        "button {"
        "   background-color: #3498db;" /* Buton arka plan rengi */
        "   border-radius: 10px;" /* Köşeleri yuvarlat */
        "   padding: 10px 20px;" /* İçerik ile kenarlar arasında boşluk bırak */
        "   color: #fff;" /* Buton metin rengi */
        "}"
        "button:hover {"
        "   background-color: #2980b9;" /* Hover efekti */
        "}", -1, NULL);

    // Provider'ı uygulamaya ekle
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    // CSS provider'ı serbest bırak
    g_object_unref(provider);

    // Pencereyi göster
    gtk_widget_show_all(window);

    // GTK main loop
    gtk_main();

    return 0;
}

