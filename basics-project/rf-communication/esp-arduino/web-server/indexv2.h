const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<style>
.card{
    max-width: 400px;
     min-height: 250px;
     background: #02b870;
     padding: 30px;
     box-sizing: border-box;
     color: #FFF;
     margin:20px;
     box-shadow: 0px 2px 18px -4px rgba(0,0,0,0.75);
}
</style>
</head>
<body>
<div class="card">
  <h1>TEMPERATURA</h1><br>
  <h2>Graus: <span id="ADCValue">0</span> C</h2><br>
</div>
<div class="card">
  <h1>LED 01</h1><br>
  <h2>Status <span id="led1st">0</span> </h2><br>
  <h2>On-Off</h2><br>
</div>

<div class="card">
  <h1>LED 02</h1><br>
  <h2>Status <span id="led2nd">0</span></h2><br>
  <h2>On-Off</h2><br>
</div>

<div class="card">
  <h1>LED 03</h1><br>
  <h2>Status <span id="led3rd">0</span></h2><br>
  <h2>On-Off</h2><br>
</div>

<script>

setInterval(() => getData(), 1000)
function getData() {
  const xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("led1st").innerHTML = this.responseText;
      document.getElementById("led2nd").innerHTML = this.responseText;
	    document.getElementById("led3rd").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "led1st", true);
  xhttp.open("GET", "led2nd", true);
  xhttp.open("GET", "led3rd", true);
  xhttp.send();
}
</script>
</body>
</html>
)=====";
