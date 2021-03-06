/*
 * DO NOT EDIT THIS FILE - it is generated by Glade.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "callbacks.h"

GtkWidget*
create_Camera_Configuration ()
{
  GtkWidget *Camera_Configuration;
  GtkWidget *vbox13;
  GtkWidget *title_bar;
  GtkWidget *vbox14;
  GtkWidget *hbox6;
  GtkWidget *vbox18;
  GtkWidget *table3;
  GtkWidget *resolution_combo;
  GList *resolution_combo_items = NULL;
  GtkWidget *combo_entry7;
  GtkWidget *quality_combo;
  GtkWidget *combo_entry8;
  GtkWidget *white_combo;
  GtkWidget *combo_entry9;
  GtkWidget *record_combo;
  GtkWidget *combo_entry10;
  GtkWidget *flash_combo;
  GtkWidget *combo_entry11;
  GtkWidget *label40;
  GtkWidget *label41;
  GtkWidget *label42;
  GtkWidget *label43;
  GtkWidget *label44;
  GtkWidget *label45;
  GtkWidget *copyright_string;
  GtkWidget *hseparator6;
  GtkWidget *hseparator5;
  GtkWidget *label48;
  GtkWidget *label49;
  GtkWidget *frame14;
  GtkWidget *date_togglebutton;
  GtkWidget *vseparator2;
  GtkWidget *frame11;
  GtkWidget *vbox15;
  GtkWidget *frame12;
  GtkWidget *vbox16;
  GtkWidget *maunual_checkbutton;
  GtkWidget *exposure_hscale;
  GtkWidget *frame13;
  GtkWidget *vbox17;
  GtkWidget *macro_checkbutton;
  GtkWidget *zoom_hscale;
  GtkWidget *hbox7;
  GtkWidget *memory_togglebutton;
  GtkWidget *date_imprint_togglebutton;
  GtkWidget *debug_togglebutton;
  GtkWidget *label39;
  GtkWidget *hbox8;
  GtkWidget *statusbar1;
  GtkWidget *statusbar2;
  GtkWidget *statusbar3;
  GtkWidget *statusbar4;
  GtkWidget *hseparator4;
  GtkWidget *hbuttonbox1;
  GtkWidget *ok_button;
  GtkWidget *apply_button;
  GtkWidget *cancel_button;
  GtkTooltips *tooltips;

  tooltips = gtk_tooltips_new ();

  Camera_Configuration = gtk_window_new (GTK_WINDOW_DIALOG);
  gtk_object_set_data (GTK_OBJECT (Camera_Configuration), "Camera_Configuration", Camera_Configuration);
  gtk_container_set_border_width (GTK_CONTAINER (Camera_Configuration), 4);
  gtk_window_set_title (GTK_WINDOW (Camera_Configuration), _("Camera Configuration"));
  gtk_window_set_modal (GTK_WINDOW (Camera_Configuration), TRUE);

  vbox13 = gtk_vbox_new (FALSE, 0);
  gtk_widget_ref (vbox13);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "vbox13", vbox13,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (vbox13);
  gtk_container_add (GTK_CONTAINER (Camera_Configuration), vbox13);

  title_bar = gtk_label_new ("");
  gtk_widget_ref (title_bar);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "title_bar", title_bar,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (title_bar);
  gtk_box_pack_start (GTK_BOX (vbox13), title_bar, FALSE, FALSE, 0);
  gtk_label_set_justify (GTK_LABEL (title_bar), GTK_JUSTIFY_LEFT);

  vbox14 = gtk_vbox_new (FALSE, 0);
  gtk_widget_ref (vbox14);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "vbox14", vbox14,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (vbox14);
  gtk_box_pack_start (GTK_BOX (vbox13), vbox14, TRUE, TRUE, 0);

  hbox6 = gtk_hbox_new (FALSE, 0);
  gtk_widget_ref (hbox6);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "hbox6", hbox6,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (hbox6);
  gtk_box_pack_start (GTK_BOX (vbox14), hbox6, TRUE, TRUE, 0);

  vbox18 = gtk_vbox_new (FALSE, 0);
  gtk_widget_ref (vbox18);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "vbox18", vbox18,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (vbox18);
  gtk_box_pack_start (GTK_BOX (hbox6), vbox18, TRUE, TRUE, 0);

  table3 = gtk_table_new (8, 2, FALSE);
  gtk_widget_ref (table3);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "table3", table3,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (table3);
  gtk_box_pack_start (GTK_BOX (vbox18), table3, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (table3), 4);
  gtk_table_set_row_spacings (GTK_TABLE (table3), 4);

  resolution_combo = gtk_combo_new ();
  gtk_widget_ref (resolution_combo);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "resolution_combo", resolution_combo,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (resolution_combo);
  gtk_table_attach (GTK_TABLE (table3), resolution_combo, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  resolution_combo_items = g_list_append (resolution_combo_items, "");
  gtk_combo_set_popdown_strings (GTK_COMBO (resolution_combo), resolution_combo_items);
  g_list_free (resolution_combo_items);

  combo_entry7 = GTK_COMBO (resolution_combo)->entry;
  gtk_widget_ref (combo_entry7);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "combo_entry7", combo_entry7,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (combo_entry7);
  gtk_entry_set_editable (GTK_ENTRY (combo_entry7), FALSE);

  quality_combo = gtk_combo_new ();
  gtk_widget_ref (quality_combo);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "quality_combo", quality_combo,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (quality_combo);
  gtk_table_attach (GTK_TABLE (table3), quality_combo, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);

  combo_entry8 = GTK_COMBO (quality_combo)->entry;
  gtk_widget_ref (combo_entry8);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "combo_entry8", combo_entry8,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (combo_entry8);
  gtk_entry_set_editable (GTK_ENTRY (combo_entry8), FALSE);

  white_combo = gtk_combo_new ();
  gtk_widget_ref (white_combo);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "white_combo", white_combo,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (white_combo);
  gtk_table_attach (GTK_TABLE (table3), white_combo, 1, 2, 2, 3,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);

  combo_entry9 = GTK_COMBO (white_combo)->entry;
  gtk_widget_ref (combo_entry9);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "combo_entry9", combo_entry9,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (combo_entry9);
  gtk_entry_set_editable (GTK_ENTRY (combo_entry9), FALSE);

  record_combo = gtk_combo_new ();
  gtk_widget_ref (record_combo);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "record_combo", record_combo,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (record_combo);
  gtk_table_attach (GTK_TABLE (table3), record_combo, 1, 2, 3, 4,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);

  combo_entry10 = GTK_COMBO (record_combo)->entry;
  gtk_widget_ref (combo_entry10);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "combo_entry10", combo_entry10,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (combo_entry10);
  gtk_entry_set_editable (GTK_ENTRY (combo_entry10), FALSE);

  flash_combo = gtk_combo_new ();
  gtk_widget_ref (flash_combo);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "flash_combo", flash_combo,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (flash_combo);
  gtk_table_attach (GTK_TABLE (table3), flash_combo, 1, 2, 4, 5,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  GTK_WIDGET_SET_FLAGS (flash_combo, GTK_CAN_FOCUS);

  combo_entry11 = GTK_COMBO (flash_combo)->entry;
  gtk_widget_ref (combo_entry11);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "combo_entry11", combo_entry11,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (combo_entry11);
  gtk_entry_set_editable (GTK_ENTRY (combo_entry11), FALSE);

  label40 = gtk_label_new (_("Resolution"));
  gtk_widget_ref (label40);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "label40", label40,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label40);
  gtk_table_attach (GTK_TABLE (table3), label40, 0, 1, 0, 1,
                    (GtkAttachOptions) (0),
                    (GtkAttachOptions) (0), 0, 0);

  label41 = gtk_label_new (_("Image Quality"));
  gtk_widget_ref (label41);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "label41", label41,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label41);
  gtk_table_attach (GTK_TABLE (table3), label41, 0, 1, 1, 2,
                    (GtkAttachOptions) (0),
                    (GtkAttachOptions) (0), 0, 0);

  label42 = gtk_label_new (_("White Balance"));
  gtk_widget_ref (label42);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "label42", label42,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label42);
  gtk_table_attach (GTK_TABLE (table3), label42, 0, 1, 2, 3,
                    (GtkAttachOptions) (0),
                    (GtkAttachOptions) (0), 0, 0);

  label43 = gtk_label_new (_("Recording Mode"));
  gtk_widget_ref (label43);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "label43", label43,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label43);
  gtk_table_attach (GTK_TABLE (table3), label43, 0, 1, 3, 4,
                    (GtkAttachOptions) (0),
                    (GtkAttachOptions) (0), 0, 0);

  label44 = gtk_label_new (_("Flash Mode"));
  gtk_widget_ref (label44);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "label44", label44,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label44);
  gtk_table_attach (GTK_TABLE (table3), label44, 0, 1, 4, 5,
                    (GtkAttachOptions) (0),
                    (GtkAttachOptions) (0), 0, 0);

  label45 = gtk_label_new (_("Copyright String"));
  gtk_widget_ref (label45);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "label45", label45,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label45);
  gtk_table_attach (GTK_TABLE (table3), label45, 0, 1, 6, 7,
                    (GtkAttachOptions) (0),
                    (GtkAttachOptions) (0), 0, 0);

  copyright_string = gtk_entry_new_with_max_length (20);
  gtk_widget_ref (copyright_string);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "copyright_string", copyright_string,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (copyright_string);
  gtk_table_attach (GTK_TABLE (table3), copyright_string, 1, 2, 6, 7,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, copyright_string, _("Set the camera's clock by entering the date and time here."), NULL);

  hseparator6 = gtk_hseparator_new ();
  gtk_widget_ref (hseparator6);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "hseparator6", hseparator6,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (hseparator6);
  gtk_table_attach (GTK_TABLE (table3), hseparator6, 1, 2, 5, 6,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (GTK_FILL), 0, 0);

  hseparator5 = gtk_hseparator_new ();
  gtk_widget_ref (hseparator5);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "hseparator5", hseparator5,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (hseparator5);
  gtk_table_attach (GTK_TABLE (table3), hseparator5, 0, 1, 5, 6,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);

  label48 = gtk_label_new ("");
  gtk_widget_ref (label48);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "label48", label48,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label48);
  gtk_table_attach (GTK_TABLE (table3), label48, 0, 1, 7, 8,
                    (GtkAttachOptions) (0),
                    (GtkAttachOptions) (0), 0, 0);

  label49 = gtk_label_new ("");
  gtk_widget_ref (label49);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "label49", label49,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label49);
  gtk_table_attach (GTK_TABLE (table3), label49, 1, 2, 7, 8,
                    (GtkAttachOptions) (0),
                    (GtkAttachOptions) (0), 0, 0);

  frame14 = gtk_frame_new (NULL);
  gtk_widget_ref (frame14);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "frame14", frame14,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (frame14);
  gtk_box_pack_start (GTK_BOX (vbox18), frame14, FALSE, FALSE, 0);

  date_togglebutton = gtk_check_button_new_with_label (_("Set Camera Date/Time to Computer's Date/Time"));
  gtk_widget_ref (date_togglebutton);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "date_togglebutton", date_togglebutton,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (date_togglebutton);
  gtk_container_add (GTK_CONTAINER (frame14), date_togglebutton);
  gtk_container_set_border_width (GTK_CONTAINER (date_togglebutton), 4);

  vseparator2 = gtk_vseparator_new ();
  gtk_widget_ref (vseparator2);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "vseparator2", vseparator2,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (vseparator2);
  gtk_box_pack_start (GTK_BOX (hbox6), vseparator2, FALSE, TRUE, 0);

  frame11 = gtk_frame_new (NULL);
  gtk_widget_ref (frame11);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "frame11", frame11,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (frame11);
  gtk_box_pack_start (GTK_BOX (hbox6), frame11, TRUE, TRUE, 0);

  vbox15 = gtk_vbox_new (FALSE, 0);
  gtk_widget_ref (vbox15);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "vbox15", vbox15,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (vbox15);
  gtk_container_add (GTK_CONTAINER (frame11), vbox15);

  frame12 = gtk_frame_new (_("Exposure Compensation"));
  gtk_widget_ref (frame12);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "frame12", frame12,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (frame12);
  gtk_box_pack_start (GTK_BOX (vbox15), frame12, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (frame12), 4);

  vbox16 = gtk_vbox_new (FALSE, 0);
  gtk_widget_ref (vbox16);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "vbox16", vbox16,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (vbox16);
  gtk_container_add (GTK_CONTAINER (frame12), vbox16);

  maunual_checkbutton = gtk_check_button_new_with_label (_("Manual Control"));
  gtk_widget_ref (maunual_checkbutton);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "maunual_checkbutton", maunual_checkbutton,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (maunual_checkbutton);
  gtk_box_pack_start (GTK_BOX (vbox16), maunual_checkbutton, FALSE, FALSE, 0);

  exposure_hscale = gtk_hscale_new (GTK_ADJUSTMENT (gtk_adjustment_new (0, -2, 2.5, 0.5, 0.5, 0.5)));
  gtk_widget_ref (exposure_hscale);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "exposure_hscale", exposure_hscale,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (exposure_hscale);
  gtk_box_pack_start (GTK_BOX (vbox16), exposure_hscale, TRUE, TRUE, 0);

  frame13 = gtk_frame_new (_("Zoom Level"));
  gtk_widget_ref (frame13);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "frame13", frame13,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (frame13);
  gtk_box_pack_start (GTK_BOX (vbox15), frame13, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (frame13), 4);

  vbox17 = gtk_vbox_new (FALSE, 0);
  gtk_widget_ref (vbox17);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "vbox17", vbox17,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (vbox17);
  gtk_container_add (GTK_CONTAINER (frame13), vbox17);

  macro_checkbutton = gtk_check_button_new_with_label (_("Macro Mode"));
  gtk_widget_ref (macro_checkbutton);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "macro_checkbutton", macro_checkbutton,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (macro_checkbutton);
  gtk_box_pack_start (GTK_BOX (vbox17), macro_checkbutton, FALSE, FALSE, 0);

  zoom_hscale = gtk_hscale_new (GTK_ADJUSTMENT (gtk_adjustment_new (0, 0, 9, 1, 1, 1)));
  gtk_widget_ref (zoom_hscale);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "zoom_hscale", zoom_hscale,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (zoom_hscale);
  gtk_box_pack_start (GTK_BOX (vbox17), zoom_hscale, TRUE, TRUE, 0);
  gtk_scale_set_digits (GTK_SCALE (zoom_hscale), 0);

  hbox7 = gtk_hbox_new (FALSE, 0);
  gtk_widget_ref (hbox7);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "hbox7", hbox7,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (hbox7);
  gtk_box_pack_start (GTK_BOX (vbox15), hbox7, FALSE, FALSE, 4);

  memory_togglebutton = gtk_toggle_button_new_with_label (_("Memory"));
  gtk_widget_ref (memory_togglebutton);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "memory_togglebutton", memory_togglebutton,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (memory_togglebutton);
  gtk_box_pack_start (GTK_BOX (hbox7), memory_togglebutton, FALSE, FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (memory_togglebutton), 5);
  gtk_widget_set_sensitive (memory_togglebutton, FALSE);
  gtk_tooltips_set_tip (tooltips, memory_togglebutton, _("Switch between internal and SmartMedia on RDC-5000"), NULL);

  date_imprint_togglebutton = gtk_toggle_button_new_with_label (_("Date Imprint"));
  gtk_widget_ref (date_imprint_togglebutton);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "date_imprint_togglebutton", date_imprint_togglebutton,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (date_imprint_togglebutton);
  gtk_box_pack_start (GTK_BOX (hbox7), date_imprint_togglebutton, FALSE, FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (date_imprint_togglebutton), 4);
  gtk_widget_set_sensitive (date_imprint_togglebutton, FALSE);
  gtk_tooltips_set_tip (tooltips, date_imprint_togglebutton, _("Turn on date imprinting on RDC-5000"), NULL);

  debug_togglebutton = gtk_toggle_button_new_with_label (_("Debugging"));
  gtk_widget_ref (debug_togglebutton);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "debug_togglebutton", debug_togglebutton,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (debug_togglebutton);
  gtk_box_pack_start (GTK_BOX (hbox7), debug_togglebutton, FALSE, FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (debug_togglebutton), 4);
  gtk_tooltips_set_tip (tooltips, debug_togglebutton, _("Toggle debugging mode on and off"), NULL);

  label39 = gtk_label_new ("");
  gtk_widget_ref (label39);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "label39", label39,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (label39);
  gtk_box_pack_start (GTK_BOX (vbox14), label39, FALSE, FALSE, 0);

  hbox8 = gtk_hbox_new (FALSE, 0);
  gtk_widget_ref (hbox8);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "hbox8", hbox8,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (hbox8);
  gtk_box_pack_start (GTK_BOX (vbox14), hbox8, FALSE, FALSE, 0);

  statusbar1 = gtk_statusbar_new ();
  gtk_widget_ref (statusbar1);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "statusbar1", statusbar1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (statusbar1);
  gtk_box_pack_start (GTK_BOX (hbox8), statusbar1, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (statusbar1), 1);

  statusbar2 = gtk_statusbar_new ();
  gtk_widget_ref (statusbar2);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "statusbar2", statusbar2,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (statusbar2);
  gtk_box_pack_start (GTK_BOX (hbox8), statusbar2, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (statusbar2), 1);

  statusbar3 = gtk_statusbar_new ();
  gtk_widget_ref (statusbar3);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "statusbar3", statusbar3,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (statusbar3);
  gtk_box_pack_start (GTK_BOX (hbox8), statusbar3, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (statusbar3), 1);

  statusbar4 = gtk_statusbar_new ();
  gtk_widget_ref (statusbar4);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "statusbar4", statusbar4,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (statusbar4);
  gtk_box_pack_start (GTK_BOX (hbox8), statusbar4, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (statusbar4), 1);

  hseparator4 = gtk_hseparator_new ();
  gtk_widget_ref (hseparator4);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "hseparator4", hseparator4,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (hseparator4);
  gtk_box_pack_start (GTK_BOX (vbox13), hseparator4, FALSE, TRUE, 0);

  hbuttonbox1 = gtk_hbutton_box_new ();
  gtk_widget_ref (hbuttonbox1);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "hbuttonbox1", hbuttonbox1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (hbuttonbox1);
  gtk_box_pack_end (GTK_BOX (vbox13), hbuttonbox1, FALSE, TRUE, 0);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (hbuttonbox1), GTK_BUTTONBOX_END);
  gtk_button_box_set_spacing (GTK_BUTTON_BOX (hbuttonbox1), 8);

  ok_button = gtk_button_new_with_label (_("Ok"));
  gtk_widget_ref (ok_button);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "ok_button", ok_button,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (ok_button);
  gtk_container_add (GTK_CONTAINER (hbuttonbox1), ok_button);
  GTK_WIDGET_SET_FLAGS (ok_button, GTK_CAN_DEFAULT);

  apply_button = gtk_button_new_with_label (_("Apply"));
  gtk_widget_ref (apply_button);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "apply_button", apply_button,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (apply_button);
  gtk_container_add (GTK_CONTAINER (hbuttonbox1), apply_button);
  GTK_WIDGET_SET_FLAGS (apply_button, GTK_CAN_DEFAULT);

  cancel_button = gtk_button_new_with_label (_("Cancel"));
  gtk_widget_ref (cancel_button);
  gtk_object_set_data_full (GTK_OBJECT (Camera_Configuration), "cancel_button", cancel_button,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (cancel_button);
  gtk_container_add (GTK_CONTAINER (hbuttonbox1), cancel_button);
  GTK_WIDGET_SET_FLAGS (cancel_button, GTK_CAN_DEFAULT);

  gtk_signal_connect (GTK_OBJECT (Camera_Configuration), "destroy",
                      GTK_SIGNAL_FUNC (on_Camera_Configuration_destroy),
                      &Camera_Configuration);
  gtk_signal_connect (GTK_OBJECT (copyright_string), "activate",
                      GTK_SIGNAL_FUNC (on_copyright_string_activate),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (copyright_string), "focus_out_event",
                      GTK_SIGNAL_FUNC (on_copyright_string_focus_out_event),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (date_togglebutton), "toggled",
                      GTK_SIGNAL_FUNC (on_date_togglebutton_toggled),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (maunual_checkbutton), "toggled",
                      GTK_SIGNAL_FUNC (on_maunual_checkbutton_toggled),
                      GTK_OBJECT(exposure_hscale));
  gtk_signal_connect (GTK_OBJECT (exposure_hscale), "focus_out_event",
                      GTK_SIGNAL_FUNC (on_exposure_hscale_focus_out_event),
                      GTK_OBJECT(maunual_checkbutton));
  gtk_signal_connect (GTK_OBJECT (macro_checkbutton), "toggled",
                      GTK_SIGNAL_FUNC (on_macro_checkbutton_toggled),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (zoom_hscale), "focus_out_event",
                      GTK_SIGNAL_FUNC (on_zoom_hscale_focus_out_event),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (memory_togglebutton), "client_event",
                      GTK_SIGNAL_FUNC (on_memory_togglebutton_event),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (date_imprint_togglebutton), "toggled",
                      GTK_SIGNAL_FUNC (on_date_imprint_togglebutton_toggled),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (debug_togglebutton), "toggled",
                      GTK_SIGNAL_FUNC (on_debug_togglebutton_toggled),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (ok_button), "clicked",
                      GTK_SIGNAL_FUNC (on_ok_button_clicked),
                      GTK_OBJECT(Camera_Configuration));
  gtk_signal_connect (GTK_OBJECT (apply_button), "clicked",
                      GTK_SIGNAL_FUNC (on_apply_button_clicked),
                      GTK_OBJECT(Camera_Configuration));
  gtk_signal_connect (GTK_OBJECT (cancel_button), "clicked",
                      GTK_SIGNAL_FUNC (on_cancel_button_clicked),
                      GTK_OBJECT(Camera_Configuration));

  gtk_widget_grab_focus (ok_button);
  gtk_widget_grab_default (ok_button);
  gtk_object_set_data (GTK_OBJECT (Camera_Configuration), "tooltips", tooltips);

  return Camera_Configuration;
}

