---
permalink: /PROJECT_DIVISION/
---

<body>
  <h1>Project Division</h1>
  <p><b>Retailer End:</b></p>
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

  <script>
    {% include scripts/accordion.js %}
  </script>
</body>
