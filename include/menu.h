#pragma once

enum MenuCode { MenuLevelSel, MenuAllMode, MenuTutorial, MenuExit };
enum MenuPause { MenuContinue, MenuBack };

enum MenuCode start_menu();
char level_selection(int *id_level);
enum MenuPause pause_menu(char level[], int id_level, int coin, int death_count);
