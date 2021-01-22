---
permalink: /PROJECT_DIVISION/
---

<body>
  <h1>Project Division</h1>
  <button class="accordion"><b>Retailer End:</b></button>
  <div class="panel">
    <br>
    <p>Its main purpose is to make sure that the included functionalities aren't re-used whenever main function is called. Also, it initializes the file names which are used to save In-game variables & strings. Hence, keeping your file names updated even if you have to rename the files in application.</p>
    <hr>
  </div>
  
  <button class="accordion"><b>Customer End:</b></button>
  <div class="panel">
    <br>
  <ul>
    <li>Our project has Maximum abstraction so that the customer's data cannot be stolen/updated from app nor from its Files.</li>
    <li>We also ensured that all sensitive data is encrypted so that no info could be stole from files.</li>
    <li>Our Application is portable, as it doesn’t require manual recompilation for generating new classes.</li>
    <li>All Input data errors are validated using the generic function & its overloaded versions.</li>
    <li>Our application is also memory efficient (i.e. vector class approach used for Items Pointer Array).</li>
  </ul>
    <hr>
  </div>

  <script>
    {% include scripts/accordion.js %}
  </script>
</body>
