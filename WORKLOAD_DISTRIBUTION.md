---
permalink: /WORKLOAD_DISTRIBUTION/
---

<body>
  <h1>Workload Distribution</h1>
  <p>Following are the (improved) functions included in this project:</p>
  <button class="accordion"><b>1. main_constructor()</b></button>
  <div class="panel">
    <br>
    <p>Its main purpose is to make sure that the included functionalities aren't re-used whenever main function is called. Also, it initializes the file names which are used to save In-game variables & strings. Hence, keeping your file names updated even if you have to rename the files in application.</p>
    <hr>
  </div>
  
  <button class="accordion"><b>2. main()</b></button>
  <div class="panel">
    <br>
    <p>This function contains the control of the whole game. User can switch to resume, new game, load game, save game, tutorial and exit from this function by simply scrolling up/down in the menu. It calls the respective functions as user’s input. In this function user can also use pre-defined short cut keys too.</p>
    <hr>
  </div>
  
  <button class="accordion"><b>3. gotoxy(int x,int y)</b></button>
  <div class="panel">
    <br>
    <p>It take coordinates (x,y) as parameters and point the cursor pointer on designated coordiantes on screen.</p>
    <hr>
  </div>
  
  <button class="accordion"><b>4. welcome_screen()</b></button>
  <div class="panel">
    <br>
    <p>It shows a welcome screen, using loops & strings.</p>
    <hr>
  </div>
  
  <button class="accordion"><b>5. cursor_pointer(int x,int y)</b></button>
  <div class="panel">
    <br>
    <p>It points the user-made rotating cursor on designated position on screen w.r.t coordinates (x,y) which are taken as parameters.</p>
    <hr>
  </div>
  
  <button class="accordion"><b>6. display_boxes()</b></button>
  <div class="panel">
    <br>
    <p>It prints boxes using loops for main-menu.</p>
    <hr>
  </div>
  
  <button class="accordion"><b>7. show_main_menu()</b></button>
  <div class="panel">
    <br>
    <p>It displays all printf commands in main-menu.</p>
    <hr>
  </div>
  
  <button class="accordion"><b>8. show_dice_menu()</b></button>
  <div class="panel">
    <br>
    <p>It displays all printf commands in dice-menu.</p>
    <hr>
  </div>
  
  <button class="accordion"><b>9. dice_settings()</b></button>
  <div class="panel">
    <br>
    <p>It basically allows user to modify dice settings (i.e. auto/manual, single/double dice options are available).</p>
    <hr>
  </div>
  
  <button class="accordion"><b>10. random_dice()</b></button>
  <div class="panel">
    <br>
    <p>It generates random value on dice as per single/double dice settings.</p>
    <hr>
  </div>
  
  <button class="accordion"><b>11. manual_dice()</b></button>
  <div class="panel">
    <br>
    <p>It generates user’s desired value on dice as per single/double dice settings.</p>
    <hr>
  </div>
  
  <button class="accordion"><b>12. display_board(int board[][10])</b></button>
  <div class="panel">
    <br>
    <p>It displays the game board for snakes & ladders, using iterative conditions.</p>
    <hr>
  </div>
  
  <button class="accordion"><b>13. show_stats(int turn_flag,int temp_cp,int temp_tc)</b></button>
  <div class="panel">
    <br>
    <p>It displays current stats of a player during the match.</p>
    <hr>
  </div>
  
  <button class="accordion"><b>14. locate_pointer_on_board(int temp_cp)</b></button>
  <div class="panel">
    <br>
    <p>It points the cursor pointer on designated position on game board, mainly using gotoxy function. To achieve size reduction in code, a complex mathematical equation is used to track the position of pointer.</p>
    <hr>
  </div>
  
  <button class="accordion"><b>15. estimated_func_time(int *const extra_time,int (*func)())</b></button>
  <div class="panel">
    <br>
    <p>It calculates the time taken by a function that is passed as parameter using function pointer and saves calculated time by assigning value on the address of the variable, which is taken as a parameter.</p>
    <hr>
  </div>
  
  <button class="accordion"><b>16. show_winning_menu()</b></button>
  <div class="panel">
    <br>
    <p>It displays some printf commands in win-menu.</p>
    <hr>
  </div>
  
  <button class="accordion"><b>17. display_standard_time(int N)</b></button>
  <div class="panel">
    <br>
    <p>It takes time in seconds as parameter and then converts it to standard time format (i.e 1 hour 20 mins 4 secs). Also, it makes sure to display in correct format sequence, means if any variable (i.e. hour/mins/sec) is 0, then it display the time without that variable.</p>
    <hr>
  </div>
  
  <button class="accordion"><b>18. main_game()</b></button>
  <div class="panel">
    <br>
    <p>It is the function in which all In-game procedures are carried out. Like, when the game starts, the flow of program is transferred to this function. It basically controls all In-game elements (i.e. snakes, ladders, player turns & positions, cursor pointer on game board, game modes, dice settings, limits, win menu, etc). Also, it is responsible for In-game time taken calculations.</p>
    <hr>
  </div>
  
  <button class="accordion"><b>19. locate_menu_pointer()</b></button>
  <div class="panel">
    <br>
    <p>It basically holds the working of Cursor pointer in New Game & Hidden File Settings Menu.</p>
    <hr>
  </div>
  
  <button class="accordion"><b>20. new_game()</b></button>
  <div class="panel">
    <br>
    <p>It prompts users for user names, game modes (in the form of Menu) & specific game mode limit. Also it re-initializes/resets all In-game variables.</p>
    <hr>
  </div>
  
  <button class="accordion"><b>21. calc_slot_capacity()</b></button>
  <div class="panel">
    <br>
    <p>It basically calculates the number of rows (i.e. slots) present in In-game variables & In-game strings files.</p>
    <hr>
  </div>
  
  <button class="accordion"><b>22. rename_data_files()</b></button>
  <div class="panel">
    <br>
    <p>It renames In-game variables & In-game strings files.</p>
    <hr>
  </div>
  
  <button class="accordion"><b>23. delete_specific_slot()</b></button>
  <div class="panel">
    <br>
    <p>Its main function is to delete the specific row (i.e. slot) in both files (using temporary file method).</p>
    <hr>
  </div>
  
  <button class="accordion"><b>24. hidden_settings()</b></button>
  <div class="panel">
    <br>
    <p>It shows hidden settings in main-menu when ‘tab’ is pressed. Moreover, it contains a unique menu for the settings (i.e. erase data files, rename files, delete specific slot, sounds (ON/OFF)).</p>
    <hr>
  </div>
  
  <button class="accordion"><b>25. password(char *const temp_password)</b></button>
  <div class="panel">
    <br>
    <p>It takes password character by character from user while hiding from others and then saves in array. After that, it copies to another array that is received as parameter through a pointer.</p>
    <hr>
  </div>
  
  <button class="accordion"><b>26. save_game()</b></button>
  <div class="panel">
    <br>
    <p>It saves the current game (only) while asking for password (twice for verification) & authentication game name from user. It also makes sure that the game name is not as same as the previous saved games.</p>
    <hr>
  </div>
  
  <button class="accordion"><b>27. load_game()</b></button>
  <div class="panel">
    <br>
    <p>It basically loads the previous game (saved by user) even when the application is refreshed, using filing-process. Moreover, it has a flexible menu for all previous saved games. Also, it makes sure that password and game-name do match, otherwise an error will be generated.</p>
    <hr>
  </div>
  
  <button class="accordion"><b>28. guide()</b></button>
  <div class="panel">
    <br>
    <p>It reads the Guide Text from a previously saved data file in colorful display.</p>
    <hr>
  </div>

  <script>
    {% include scripts/accordion.js %}
  </script>
</body>
