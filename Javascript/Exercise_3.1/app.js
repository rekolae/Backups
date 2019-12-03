var express = require("express");
var xss_filter = require("xss-filters");
var cookie_parser = require("cookie-parser");
var express_sanitizer = require("express-sanitizer");

var server = express();

server.use(express.urlencoded({extended: true}));
server.use(cookie_parser());
server.use(express_sanitizer());

var html_form = '<!doctype html>' +
'<html lang="en"><head>' +
'<meta charset="utf-8">' +
'<title>Cookies!</title>' +
'</head><body>' +
'<form action="/cookiejar" method="post">' +
'<input type="hidden" id="firstCookie" name="firstCookie" value="Joseph">' +
'<input type="hidden" id="secondCookie" name="secondCookie" value="Joestar">' +
'<input type="hidden" id="thirdCookie" name="thirdCookie" value="JoJo">' +
'<button type="submit">Submit super secret cookies!</button>' +
'</form></html>';

var cookie_link = '<!doctype html><html lang="en"><head><meta charset="utf-8"><title>Cookies!</title></head><body><a href="/requestCookies">Go see the cookies!</a></body></html>';

// Handles GET requests to "/cookiejar" and displays submit button
server.get("/cookiejar", function (req, res) {
  console.log("Got a GET request to '/cookiejar'");
  res.send(html_form);
});

// Handles POST requests to "/cookiejar"
server.post("/cookiejar", function (req, res) {
  console.log("Got a POST request to '/cookiejar'");

  // Sanitize cookie values
  res.cookie("username", req.sanitize(req.body.firstCookie));
  res.cookie("password", req.sanitize(req.body.secondCookie));
  res.cookie("userrole", req.sanitize(req.body.thirdCookie));

  // Display link for inspecting cookies
  res.send(cookie_link);
});

// Handles GET requests to "/requestCookies"
server.get("/requestCookies", function (req, res) {
  console.log("Got a GET request to '/requestCookies'");
  res.write('<!doctype html><html lang="en"><head><meta charset="utf-8"><title>Cookies!</title></head><body><ul>');

  // Loop through cookies and insert sanitized cookie values to page
  for (var cookie_name in req.cookies) {
    cookie_val = xss_filter.inHTMLData(req.cookies[cookie_name]);
    res.write("<li>" + cookie_name + ": " + cookie_val + "</li>");
  }

  res.end('</ul></body></html>');
});

// Create server and listen to 127.0.0.1:3000
server.listen(3000, "0.0.0.0", function () {
  console.log("Server running at 127.0.0.1:3000");
});
