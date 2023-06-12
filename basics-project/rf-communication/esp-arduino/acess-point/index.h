const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
  <head>
    <meta http-equiv='refresh' content='3'>
    <style>
      button { font-size:50px; }  
      table, th, td { border: 2px solid black; padding: 5px; font-size:50px;}
      table { border-spacing: 15px; }
    </style>
  </head>
  
  <body>
  <table style="width:100%">
  <tr>
    <td>Componente</td>
    <td>Ligar</td>
    <td>Desligar</td>
    <td>Status</td>
  </tr>
  <tr>
    <td>LED 1</td>
    <td><a href="led1on" target="myIframe1"> <button> ON </button> </a></td>
    <td><a href="led1of" target="myIframe1"> <button> OF </button> </a></td>
    <td><iframe name="myIframe1" frameborder="0" scrolling="0" width="100px" height="30px"></iframe></td>
  </tr>	
  <tr>
    <td>LED 2</td>
    <td><a href="led2on" target="myIframe2"> <button> ON </button> </a></td>
    <td><a href="led2of" target="myIframe2"> <button> OF </button> </a></td>
    <td><iframe name="myIframe2" frameborder="0" scrolling="0" width="100px" height="30px"></iframe></td>
  </tr>	
  <tr>
    <td>LED 3</td>
    <td><a href="led3on" target="myIframe3"> <button> ON </button> </a></td>
    <td><a href="led3of" target="myIframe3"> <button> OF </button> </a></td>
    <td><iframe name="myIframe3" frameborder="0" scrolling="0" width="100px" height="30px"></iframe></td>
  </tr>
  <tr>
    <td>LED TODAS</td>
    <td><a href="ledtodason" target="myIframe4"> <button> ON </button> </a></td>
    <td><a href="ledtodasof" target="myIframe4"> <button> OF </button> </a></td>
    <td><iframe name="myIframe4" frameborder="0" scrolling="0" width="100px" height="30px"></iframe></td>
  </tr>
<hr>
</body>
</html>
)=====";