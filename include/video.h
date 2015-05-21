

/* Limpia la pantalla */
void k_clear_screen();

/* Escribe un byte en pantalla */
void writeScreen(byte);

/* Repinta la pantalla */
void repaintScreen();

/* Repinta la linea pasada por parametro */
void repaintLine(int);

/* Repinta la primer linea */
void repaintFirstLine();

/* Corre la pantalla una linea para arriba */
void jumpLine();

/* Actualiza la posicion del cursor en la pantalla */
void update_cursor();
