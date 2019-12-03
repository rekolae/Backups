var express = require("express");
var helmet = require("helmet");
var xssFilter = require("xss-filters");
var mysql = require("mysql");

var server = express();
server.use(helmet());
server.use(express.json());

// Set connection pooling parameters
var connectionPool = mysql.createPool({
  connectionLimit : 10,
  host            : "localhost",
  port            : "3306",
  user            : "root",
  password        : "MyUnsafePassword",
  database        : "Biota"
});


// Uncomment the function call below to clear the created table
//clearTableData();

initDB();

// This function can be used to clear all existing table data
// Useful for testing purposes
function clearTableData () {
  connectionPool.query("DROP TABLE Fauna", function (err, result) {
      if (err) throw err;
      console.log("Table deleted!");
  });
}

// Creates the database and the table on first run
function initDB () {
  var command = "CREATE DATABASE IF NOT EXISTS Biota";
  connectionPool.query(command, function (err, result) {
    if (err) {
      console.error("Error during database init: " + err);
      process.exit(1);
    }

    console.log("Database ready!");
  });

  command = "CREATE TABLE IF NOT EXISTS Fauna (speciesName VARCHAR(20), maximumWeight BIGINT)";
  connectionPool.query(command, function (err, result) {
    if (err) {
      console.error("Error during table init: " + err);
      process.exit(1);
    }

    console.log("Table ready!");
  });
}

// Insert user submitted data to database after validating and escaping it
function insert_data (json, res) {
  res.setHeader("Content-Type", "text/plain");
  var species = json.speciesName;
  var weight = json.maximumWeight;

  // Check if species name is a string
  if (typeof(species) !== "string") {
    res.statusCode = 500;
    if (typeof(species) === "undefined") {
      console.error("Parameter 'speciesName' was not defined!");
      res.send("Species name was not specified!\n");
    }

    else {
      console.error("Parameter 'speciesName' type is invalid!");
      res.send("Species name is not a string!\n");
    }
    return;
  }

  // Check if species weight was defined
  if (typeof(weight) === "undefined") {
    res.statusCode = 500;
    console.error("Parameter 'maximumWeight' was not defined!");
    res.send("Species weight was not specified!\n");
    return;
  }

  // Try to convert given weight to BigInt type
  try {
    weight = BigInt(weight);
  }

  catch (err) {
    console.error("Parameter 'maximumWeight' couldn't be converted to BigInt!");
    res.statusCode = 500;
    res.send("Species maximum weight could not be converted to BigInt!\n");
    return;
  }

  // Check if species already exists in the database
  var command = "SELECT * FROM Fauna WHERE speciesName = ?";
  connectionPool.query(command, [species], function (err, result) {

    // If species exists -> update entry with new weight
    if (result.length !== 0) {
      command = "UPDATE Fauna SET maximumWeight =? WHERE speciesName =?";
      connectionPool.query(command, [weight, species], function (err, result) {
        if (err) {
          console.log(err);
          res.statusCode = 500;
          res.send("Error occured while updating data!\n");
        }

        else {
          console.log("Existing entry updated");
          res.statusCode = 200;
          res.send("Database entry updated\n");
        }
      });
    }

    // If not -> create new entry
    else {
      command = "INSERT INTO Fauna SET speciesName = ?, maximumWeight = ?";
      connectionPool.query(command, [species, weight], function (err, result) {
        if (err) {
          console.log(err);
          res.statusCode = 500;
          res.send("Error occured while adding new data to database!\n");
        }

        else {
          console.log("New entry inserted");
          res.statusCode = 200;
          res.send("New entry added to database\n");
        }
      });
    }
  });
}

// Send table data to the user in a html page (and log the table also)
function showTableData (res) {
  command = "SELECT * FROM Fauna";
  connectionPool.query(command, function (err, result) {
    if (err) {
      res.setHeader("Content-Type", "text/plain");
      console.error("Error getting table data!");
      res.statusCode = 500;
      res.send("Couldn't get table data!");
    }

    else {
      console.log("Showing table data");
      res.setHeader("Content-Type", "text/html");
      res.statusCode = 200;

      res.write('<!doctype html><html lang="en"><head><meta charset="utf-8"><title>Table data</title></head><body><ul>');

      // Loop through table data and insert sanitized values to page
      for (var entry in result) {
        console.log(result[entry]);
        name = xssFilter.inHTMLData(result[entry].speciesName);
        weight = xssFilter.inHTMLData(result[entry].maximumWeight);
        res.write("<li>" + name + ": " + weight + "kg</li>");
      }

      res.end('</ul></body></html>');
    }
  });
}

// Catch POST requests to "/species"
server.post("/species", function (req, res) {
  console.log("Got a POST request to '/species'");
  insert_data(req.body, res);
});

// Catch GET requests to "/species"
server.get("/species", function (req, res) {
  console.log("Got a GET request to '/species'");
  showTableData(res);
});

// Catch requests to "/species" with invalid methods
server.all("/species", function (req, res) {
  console.log("Got request with invalid method to to '/species'!");
  res.setHeader("Content-Type", "text/plain");
  res.statusCode = 405;
  res.send("Method not allowed!\n");
});

// Catch all other requests
server.all("/*", function (req, res) {
  res.setHeader("Content-Type", "text/plain");
  res.statusCode = 404;
  res.send("Page not found!\n");
});

// Create server and listen to 127.0.0.1:3000
server.listen(3000, "0.0.0.0", function () {
  console.log("Server running at 127.0.0.1:3000");
});
