/*
ATSH-MISC.C
Oscar Pablo Di Liscia / Juan Pampin
 */

#include "atsh.h"

extern GtkWidget           *win_main;
extern GtkAccelGroup       *accel_group;
extern GtkTooltips         *tooltips;




/*
 * CreateMenuItem
 *
 * Creates an item and puts it in the menu and returns the item.

 */
GtkWidget *CreateMenuItem (GtkWidget *menu, 
                           char *szName, 
                           char *szAccel,
                           char *szTip, 
                           GtkSignalFunc func,
                           gpointer data)
{
    GtkWidget *menuitem;

    /* --- If there's a name, create the item and put a
     *     Signal handler on it.
     */
    if (szName && strlen (szName)) {
        menuitem = gtk_menu_item_new_with_label (szName);
        gtk_signal_connect (GTK_OBJECT (menuitem), "activate",
                    GTK_SIGNAL_FUNC(func), data);
    } else {
        /* --- Create a separator --- */
        menuitem = gtk_menu_item_new ();
    }

    /* --- Add menu item to the menu and show it. --- */
    gtk_menu_append (GTK_MENU (menu), menuitem);
    gtk_widget_show (menuitem);

    if (accel_group == NULL) {
        accel_group = gtk_accel_group_new ();
        gtk_accel_group_attach (accel_group, GTK_OBJECT (win_main));
    }

    /* --- If there was an accelerator --- */
    if (szAccel && szAccel[0] == '^') {
        gtk_widget_add_accelerator (menuitem, 
                                    "activate", 
                                    accel_group,
                                    szAccel[1], 
                                    GDK_CONTROL_MASK,
                                    GTK_ACCEL_VISIBLE);
    }

    /* --- If there was a tool tip --- */
    if (szTip && strlen (szTip)) {
        gtk_tooltips_set_tip (tooltips, menuitem, szTip, NULL);
    }

    return (menuitem);
}




/*
 * CreateSubMenu
 *
 * Create a submenu off the menubar.
 *
 * menubar - obviously, the menu bar.
 * szName - Label given to the new submenu
 *
 * returns new menu widget
 */
GtkWidget *CreateSubMenu (GtkWidget *menubar, char *szName)
{
    GtkWidget *menuitem;
    GtkWidget *menu;
 
    /* --- Create menu --- */
    menuitem = gtk_menu_item_new_with_label (szName);

    /* --- Add it to the menubar --- */
    gtk_widget_show (menuitem);
    gtk_menu_append (GTK_MENU (menubar), menuitem);

    /* --- Get a menu and attach to the menuitem --- */
    menu = gtk_menu_new ();
    gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem), menu);

    return (menu);
}


/*
 * CreateBarSubMenu
 *
 * Create a submenu within an existing submenu.  (In other words, it's not
 * the menubar.)
 *
 * menu - existing submenu
 * szName - label to be given to the new submenu off of this submenu
 *
 * returns new menu widget 
 */ 
GtkWidget *CreateBarSubMenu (GtkWidget *menu, char *szName)
{
    GtkWidget *menuitem;
    GtkWidget *submenu;
 
    /* --- Create menu --- */
    menuitem = gtk_menu_item_new_with_label (szName);

    /* --- Add it to the menubar --- */
    gtk_menu_bar_append (GTK_MENU_BAR (menu), menuitem);
    gtk_widget_show (menuitem);

    /* --- Get a menu and attach to the menuitem --- */
    submenu = gtk_menu_new ();
    gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem), submenu);

    /* ---  --- */
    return (submenu);
}



////////////////////////////////////////////////////////////////////////////
void Create_menu (GtkWidget *menubar)
{   
  GtkWidget *menu;
  GtkWidget *menuitem;  

  /* -----------------
     --- File menu ---
     ----------------- */
    menu =(GtkWidget *)( CreateBarSubMenu (menubar, "File"));

    menuitem = CreateMenuItem (menu, "Load ATS file", "^L", 
                     "Load Analysis File", 
                     GTK_SIGNAL_FUNC (filesel),"atsin");
    
    menuitem = CreateMenuItem (menu, "Save ATS file", "^S", 
                     "Save Analysis File", 
                     GTK_SIGNAL_FUNC (filesel),"atsave");

    menuitem = CreateMenuItem (menu, NULL, NULL, //SEPARADOR
   
                  NULL, NULL, NULL);
    
    menuitem = CreateMenuItem (menu, "New ATS File", "^I", 
                     "Select and Analyze input soundfile", 
                     GTK_SIGNAL_FUNC (create_ana_dlg),NULL);

    menuitem = CreateMenuItem (menu, "Set Output SoundFile", "^O", 
                     "Select output soundfile", 
                     GTK_SIGNAL_FUNC (filesel),"outsel");
    /*
     menuitem = CreateMenuItem (menu, "Set Audio Editor", "^U", 
                     "Choose Soundfiles Editor", 
                     GTK_SIGNAL_FUNC (filesel), "audsel");
    */

    menuitem = CreateMenuItem (menu, NULL, NULL, //SEPARATOR
                     NULL, NULL, NULL);
    
    menuitem = CreateMenuItem (menu, "Quit", "^Q", 
                     "Exit ATSH", 
                     GTK_SIGNAL_FUNC (EndProgram),NULL);

    /* -----------------
       --- Edit menu ---
       ----------------- */
    menu = (GtkWidget *)CreateBarSubMenu (menubar, "Edit");
    menuitem = CreateMenuItem (menu, "Undo", "^0", 
                     "Undo last edition", 
                     GTK_SIGNAL_FUNC (do_undo),GINT_TO_POINTER(-1));
    //menuitem = CreateMenuItem (menu, "Redo", "^1", 
    //                 "Redo last edition", 
    //                 GTK_SIGNAL_FUNC (do_undo),GINT_TO_POINTER(1));

    menuitem = CreateMenuItem (menu, NULL, NULL, //SEPARATOR
                     NULL, NULL, NULL);
    menuitem = CreateMenuItem (menu, "Select All", "^1", 
                     "Select entire file", 
                     GTK_SIGNAL_FUNC (sel_all), NULL);
    menuitem = CreateMenuItem (menu, "Unselect All", "^2", 
                     "Unselect all", 
                     GTK_SIGNAL_FUNC (sel_un), NULL);
    menuitem = CreateMenuItem (menu, "Select even", "^3", 
                     "Select even Partials", 
                     GTK_SIGNAL_FUNC (sel_even), NULL);
    menuitem = CreateMenuItem (menu, "Select Odd", "^4", 
                     "Select Odd Partials", 
                     GTK_SIGNAL_FUNC (sel_odd), NULL);
    menuitem = CreateMenuItem (menu, "Invert Selection", "^5", 
                     "Select the unselected partials", 
                     GTK_SIGNAL_FUNC (revert_sel), NULL);
    menuitem = CreateMenuItem (menu, "Smart Selection", "^6", 
                     "Select partials using rules", 
                     GTK_SIGNAL_FUNC (create_sel_dlg), NULL);

    menuitem = CreateMenuItem (menu, NULL, NULL, //SEPARATOR
                     NULL, NULL, NULL);
    
    menuitem = CreateMenuItem (menu, "Edit Amplitude", "^7", 
                     "Change Amplitude of Seleccion", 
                 GTK_SIGNAL_FUNC (edit_amp),NULL);

    menuitem = CreateMenuItem (menu, "Normalize Selection", "^8", 
			       "Reescale all amplitudes according to 1/max.amp.", 
			       GTK_SIGNAL_FUNC (normalize_amplitude), NULL);

    menuitem = CreateMenuItem (menu, "Edit Frequency", "^9", 
			       "Change Frequency of Seleccion", 
			       GTK_SIGNAL_FUNC (edit_freq), NULL);
    
    
    
    /* -----------------
       --- View menu ---
       ----------------- */
    menu = (GtkWidget *)CreateBarSubMenu (menubar, "View");
    menuitem = CreateMenuItem (menu, "List", "^T", 
                     "View Amp., Freq. and Phase on a list", 
                     GTK_SIGNAL_FUNC (list_view), NULL);
    menuitem = CreateMenuItem (menu, NULL, NULL, //SEPARADOR
                     NULL, NULL, NULL);
    menuitem = CreateMenuItem (menu, "Spectrum (lines / dashes)", "^C", 
                     "View Spectrum Plot(drawn either with lines or dashes)", 
                     GTK_SIGNAL_FUNC (set_spec_view), NULL);

    menuitem = CreateMenuItem (menu, "Residual", "^D", 
			       "View Residual Plot", 
			       GTK_SIGNAL_FUNC (set_res_view), NULL);
   
    menuitem = CreateMenuItem (menu, NULL, NULL, //SEPARADOR
                     NULL, NULL, NULL);
    menuitem = CreateMenuItem (menu, "unzoom", "^U", 
                     "zoom out full", 
                     GTK_SIGNAL_FUNC (unzoom), NULL);
    menuitem = CreateMenuItem (menu, "zoom selection", "^Z", 
                     "zoom selected region", 
                     GTK_SIGNAL_FUNC (zoom_sel), NULL); 
    /*
    menuitem = CreateMenuItem (menu, "selected only", "^Y", 
                     "view only selected", 
                     GTK_SIGNAL_FUNC (sel_only), NULL);
    */
    menuitem = CreateMenuItem (menu, "all / only selection", "^W", 
			       "switch between view only selection /view all", 
			       GTK_SIGNAL_FUNC (sel_only), NULL);
    menuitem = CreateMenuItem (menu, NULL, NULL, //SEPARADOR
                     NULL, NULL, NULL);
    menuitem = CreateMenuItem (menu, "Data on Header", "^E", 
                     "view specs of ATS file", 
                     GTK_SIGNAL_FUNC (show_header), NULL);
    /* -----------------
       --- Analysis menu ---
       ----------------- */
    /*
     menu = (GtkWidget *)CreateBarSubMenu (menubar, "Analysis");
     menuitem = CreateMenuItem (menu, "Parameters", "^T", 
                      "Set Analysis Parameters", 
                      GTK_SIGNAL_FUNC (create_ana_dlg), NULL);
    */
    //menuitem = CreateMenuItem (menu, NULL, NULL, //SEPARADOR
    //                 NULL, NULL, NULL);
    //menuitem = CreateMenuItem (menu, "Analyze", "^Z", 
    //                 "Analyze Soundfile", 
    //                 GTK_SIGNAL_FUNC (PrintFunc), "Analyze");
    /* -----------------
       --- Synthesis  menu ---
       ----------------- */
    menu = (GtkWidget *)CreateBarSubMenu (menubar, "Synthesis");
    
    
    menuitem = CreateMenuItem (menu, "Parameters", "^P", 
                     "Set synthesis parameters and resyntezise", 
                     GTK_SIGNAL_FUNC (get_sparams), "Parameters");
    /*
    menuitem = CreateMenuItem (menu, "Edit Output Soundfile", "^E", 
                     "Load Output Soundfile in the Selected Editor", 
                     GTK_SIGNAL_FUNC (edit_audio), "edit soundfile");
    */ 
    
    menuitem = CreateMenuItem (menu, NULL, NULL, //SEPARADOR
                     NULL, NULL, NULL);
    menuitem = CreateMenuItem (menu, "Resynthesize", "^R", 
                     "Resynthesize", 
                     GTK_SIGNAL_FUNC (do_synthesis), "Resynthesize");
    

    /* -----------------
       --- Help ---
       ----------------- */
    menu = (GtkWidget *)CreateBarSubMenu (menubar, "Help");
    /*
    menuitem = CreateMenuItem (menu, "Help", "^H", 
                     "View help file(HTML format)", 
                     GTK_SIGNAL_FUNC (PrintFunc), "help");
    */
    menuitem = CreateMenuItem (menu, "About", "^A", 
                     "About this program", 
                     GTK_SIGNAL_FUNC (about), NULL);
    
return;

}
