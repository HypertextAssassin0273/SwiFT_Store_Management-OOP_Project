---
permalink: /PROJECT_DIVISION/
---

<body>
  <h1>Project Division</h1>
  <button class="accordion"><b>Retailer End:</b></button>
  <div class="panel">
    <ul>
      <li>Retailer account is password protected with all admin privileges.</li>
      <li>Retailer can change Category of Items.</li>
      <li>Retailer can create new Category at runtime.</li>
      <li>Retailer can add/delete/move/copy/swap/update items randomly.</li>
      <li>Retailer can create/update/delete multiple databases (which can be selected to show on customer menu).</li>
      <li>While deleting, other databases are Renamed in order to remain synced with the app.</li>
      <li>All Data-Bases can be encrypted/decrypted & can be viewed while encrypted.</li>
      <li>Public Keys are available in a separate .txt file.</li>
    </ul>
    <hr>
  </div>
  
  <button class="accordion"><b>Customer End:</b></button>
  <div class="panel">
    <ul>
      <li>Customer can continue shopping after adding items to the cart unless he proceeds to checkout.</li>
      <li>Items can be added randomly from the list.</li>
      <li>Active Data-Base gets updated when customer proceeds to checkout.</li>
    </ul>
    <hr>
  </div>

  <script>
    {% include scripts/accordion.js %}
  </script>
</body>
