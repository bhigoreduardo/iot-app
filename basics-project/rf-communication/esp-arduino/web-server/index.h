const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.16.0/umd/popper.min.js"></script>
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.4.1/js/bootstrap.min.js"></script>
</head>
<body>
<div class="container">
  <h2>Monitoramento</h2>
  <div class="card">
    <div class="card-body">
      <h1>Contagem</h1><br>
      <h2>Nr.: <span id="count">0</span></h2><br>
      <h2>Informações adicionais da temperaruta</h2><br>
    </div>
  </div>
  <br>
  <div class="card bg-primary text-white">
    <div class="card-body">
      <h1>LED 01</h1><br>
      <h2>Status: <b><span id="lead1st">0</span></b> </h2><br>
      <h2>On-Off</h2><br>
    </div>
  </div>
  <br>
  <div class="card bg-success text-white">
    <div class="card-body">
      <h1>LED 02</h1><br>
      <h2>Status:  <b><span id="lead2nd">0</span></b> </h2><br>
      <h2>On-Off</h2><br>
    </div>
  </div>  
  <br>
  <div class="card bg-warning text-white">
    <div class="card-body">
      <h1>LED 03</h1><br>
      <h2>Status:  <b><span id="lead3rd">0</span></b> </h2><br>
      <h2>On-Off</h2><br>
    </div>
  </div>  
</div>

<script>
const xhttp = new XMLHttpRequest();

setInterval(() => handleCount(), 1000);
function handleCount() {
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("count").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "count", true);
  xhttp.send();
}

setInterval(() => readLead1st(), 1000);
function readLead1st() {
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("lead1st").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "led1st", true);
  xhttp.send();
}

setInterval(() => readLed2nd(), 1000);
function readLed2nd() {
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200)
    {
      document.getElementById("lead2nd").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "lead2nd", true);
  xhttp.send();
}

setInterval(() => readLead3rd(), 1000);
function readLead3rd() {
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("lead3rd").innerHTML = this.responseText;      
    }
  };
  xhttp.open("GET", "lead3rd", true);
  xhttp.send();
}
</script>
</body>
</html>
)=====";
