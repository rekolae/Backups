var event_emitter = require("events");
var http = require("http");
var fs = require("fs");

var my_emitter = new event_emitter();

var server = http.createServer(function (request, response) {

  // Generate random number between 1 and 2019
  var random_num = Math.floor(Math.random() * 2019) + 1;

  my_emitter.emit("cryptic", response, random_num);
});

// Listen to specified port and run function when someone accesses the server
server.listen(3000, "0.0.0.0");
console.log("Server running at 127.0.0.1:3000");

my_emitter.on("cryptic", function (response, random_num) {

  // Write the generated random number to a file
  var file = fs.createWriteStream("./top_secret.txt");
  file.write(random_num.toString());
  file.end();

  my_emitter.emit("sendResponse", response, random_num);
});

my_emitter.on("sendResponse", function (response, random_num) {

  // Set server response parameters
  response.statusCode = 200;
  response.setHeader("Content-Type", "text/plain");
  response.write(random_num.toString());

  response.end();
});
