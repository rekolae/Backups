var http = require("http");
var fs = require("fs");
var xss_filter = require("xss-filters");


// Save given data to "db" file
function import_data(data, path, response) {

  // Check if request path is correct
  if (path === "/data/import") {
    response.setHeader("Content-Type", "text/plain");

    fs.writeFile("./db", data, function (err) {

      // If data could not be saved -> give error
      if (err) {
        console.log("Write error");
        response.statusCode = 500;
        response.write("Error: couldn't write data to file!");
        response.end();
      }

      else {
        console.log("Wrote data to file");
        response.statusCode = 200;
        response.write("Data was successfully written to file!");
        response.end();
      }
    });
  }

  else {
    console.log("Wrong write path recieved");
    response.statusCode = 404;
    response.write("404 Not found, wrong path!");
    response.end();
  }
}

// Read data from "db" file if it exists
function export_data(path, response) {

  // Check if request path is correct
  if (path === "/data/export") {
    response.setHeader("Content-Type", "text/plain");

    fs.readFile("./db", function (err, data) {

      // If file doesn't exist -> give error
      if (err && err.code === 'ENOENT') {
        console.log("File not found");
        response.statusCode = 500;
        response.write("Couldn't read data from file, file not found!");
        response.end();
      }

      // If some other error happens while reading file -> give error
      else if (err) {
        console.log("File not found");
        response.statusCode = 500;
        response.write("Couldn't read data from file!");
        response.end();
      }

      else {
        console.log("Read data from file");
        data = xss_filter.inHTMLData(data.toString()); // Filter fetched data
        response.statusCode = 200;
        response.write("Data read from file: \n" + data);
        response.end();
      }
    });
  }

  else {
    console.log("Wrong read path recieved");
    response.statusCode = 404;
    response.write("404 Not found, wrong path!");
    response.end();
  }
}

// Create server that handels requests
var server = http.createServer(function (request, response) {
  var fullUrl = 'http://' + 'none' + request.url;
  var url = new URL(fullUrl);

  if (request.method == "PUT") {

    // Get data when ready and save the data
    request.on("data", function (data) {
      import_data(data, url.pathname, response);
    });
  }

  else if (request.method == "GET") {
    export_data(url.pathname, response);
  }

  // If any other method is used than PUT or GET -> give error
  else {
    response.statusCode = 405;
    response.setHeader("Content-Type", "text/plain");
    response.write("Method " + request.method + " not allowed!");
    response.end();
  }
});

// Listen to specified port and run function when someone accesses the server
server.listen(3000, "0.0.0.0");
console.log("Server running at 127.0.0.1:3000");
