require("dotenv").config();
const http = require("http");
const fs = require("fs");
const SerialPort = require("serialport");
const io = require("socket.io");

const index = fs.readFileSync("index.html");

const parsers = SerialPort.parsers;
const parser = new parsers.Readline({
  delimiter: "\r\n",
});
const port = new SerialPort(process.env.CLIENT_SERIAL_PORT, {
  baudRate: process.env.CLIENT_BAUDRATE,
  dataBits: 8,
  parity: "none",
  stopBits: 1,
  flowControl: false,
});
port.pipe(parser);

const app = http.createServer(function (req, res) {
  res.writeHead(200, { "Content-Type": "text/html" });
  res.end(index);
});

io.listen(app);

io.on("connection", function (socket) {
  console.log("Node is listening to port");
});

parser.on("data", function (data) {
  console.log("Received data from port: " + data);

  io.emit("data", data);
});

app.listen(process.env.SERVER_PORT, () =>
  console.log(`Server on: http://localhost:${process.env.SERVER_PORT}`)
);
