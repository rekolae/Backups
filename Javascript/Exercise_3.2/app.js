var express = require("express");
var express_sanitizer = require("express-sanitizer");
var session = require("express-session");

var server = express();

server.use(express.urlencoded({extended: true}));
server.use(express_sanitizer());

// Setup session parameters
server.use(session({
  secret: "JoJo",
  resave: true,
  saveUninitialized: true,
}));


server.use(function (req, res, next) {
  // Set initial color values for current and previous colors
  if (req.session.backgroundColor === undefined) {
    req.session.backgroundColor = "#0080ff";
  }

  if (req.session.previousBackgroundColor === undefined) {
    req.session.previousBackgroundColor = "#408080";
  }

  next();
});

server.get("/setBgColor", function (req, res) {
  // Send the html page with the color picker input
  res.send('<!doctype html><html lang="en"><head>' +
  '<meta charset="utf-8"><title>Set the color!</title></head>' +
  '<body style="background-color:' + req.session.backgroundColor + '">' +
  '<form action="/viewBgColor" method="POST">' +
  '<input type="color" id="newBgColor" name="newBgColor" value="'+ req.session.backgroundColor + '">' +
  '<button type="submit">Submit new color!</button>' +
  '</form></html>');
});

server.post("/viewBgColor", function (req, res) {
  // Set new and previous colors
  req.session.previousBackgroundColor = req.session.backgroundColor;
  req.session.backgroundColor = req.sanitize(req.body.newBgColor);

  // Send the html page with a new color set as the background color
  res.send('<!doctype html><html lang="en"><head>' +
  '<meta charset="utf-8"><title>Color ${req.session.backgroundColor}</title></head>' +
  '<body style="background-color:' + req.session.backgroundColor + '">' +
  '<form action="/viewBgColor" method="POST">' +
  '<input type="color" id="newBgColor" name="newBgColor" value="'+ req.session.backgroundColor + '">' +
  '<button type="submit">Submit new color!</button>' +
  '</form><form action="/viewBgColor" method="POST">' +
  '<input type="hidden" id="newBgColor" name="newBgColor" value="'+ req.session.previousBackgroundColor + '">' +
  '<button type="submit">Go back to previous color</button>' +
  '</form><form action="/clearSession" method="POST">' +
  '<button type="submit">Clear session data</button>' +
  '</form></html>');
});

// Destroy session data and display message to user
server.post("/clearSession", function (req, res) {
  req.session.destroy(function(err) {
    if (err) {
      res.statusCode = 500;
      res.send("Error happened while destroying user session!");
    }

    else {
      res.statusCode = 200;
      res.send('User session data was successfully destroyed. <!doctype html><html lang="en"><head><meta charset="utf-8"><title>Cookies!</title></head><body><a href="/setBgColor">Return to main page</a></body></html>');
    }
  });
});

// Redirect all other requests to "/setBgColor"
server.all("/*", function (req, res) {
  res.redirect("/setBgColor");
});

// Create server and listen to 127.0.0.1:3000
server.listen(3000, "0.0.0.0", function () {
  console.log("Server running at 127.0.0.1:3000");
});
