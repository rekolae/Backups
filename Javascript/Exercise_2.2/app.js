var finalhandler = require('finalhandler');
var http = require('http');
var fs = require("fs");
var router_module = require('router');
var xss_filter = require("xss-filters");


// Save given data to "web_text.txt" file
function import_data(data, request, response) {

  // Init error response handler
  var handle_error = finalhandler(request, response);

  fs.appendFile("./web_text.txt", data.toString() + "\n", function (err) {

    // If data could not be saved -> give error
    if (err) {
      console.log("Write error!");
      handle_error(err);
    }

    else {
      console.log("Wrote data to file");
      response.statusCode = 200;
      response.setHeader("Content-Type", "text/plain");
      response.write("Data was successfully written to file!");
      response.end();
    }
  });
}

// Read data from "web_text.txt" file if it exists
function export_data(request, response) {

  // Init error response handler
  var handle_error = finalhandler(request, response);

  fs.readFile("./web_text.txt", function (err, data) {

    // If data could not be saved -> give error
    if (err) {
      console.log("Read error!");
      handle_error(err);
    }

    else {
      console.log("Read data from file");
      data = xss_filter.inHTMLData(data.toString()); // Filter fetched data
      response.statusCode = 200;
      response.setHeader("Content-Type", "text/plain");
      response.write("Data read from file: \n" + data);
      response.end();
    }
  });
}

// Init routing
var router = router_module();

router.route("/resources")

  // Handle GET requests to the path "/resources"
  .get(function (request, response) {
    export_data(request, response);
  })

  // Handle POST requests to the path "/resources"
  .post(function (request, response) {
    // Get data when ready and save the given data
    request.on("data", function (data) {
      import_data(data, request, response);
    });
  })

  // Handle all other methods to the path "/resources"
  .all(function (request, response) {
    console.log("Method not allowed!");
    response.setHeader("Content-Type", "text/plain");
    response.statusCode = 405;
    response.end();
  });

// Create server with routing
var server = http.createServer(function (request, response) {
  router(request, response, finalhandler(request, response));
});

// Listen to specified port and run function when someone accesses the server
server.listen(3000, "0.0.0.0");
console.log("Server running at 127.0.0.1:3000");
