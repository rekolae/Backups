var fs = require("fs");
var proc = require("process");

var path = "./strings.txt";

// If no arguments are given -> Exit with code 1
if (proc.argv.length === 2) {
  console.log("Error parsing command line!");
  proc.exit(1);
}

// Get given arguments
var args = proc.argv.slice(2);

// Loop through all given arguments and execute wanted operations
for (var i = 0; i < args.length; i++) {
  if (args[i] === "delete") {

    // Try to delete file
    fs.unlink(path, function (err) {
      if (err) {
        console.log("Can't delete file that doesn't exist!");
      }

      else {
        console.log("File deleted!");
      }
    });
  }

  else {

    // Try to append given arguments to the file
    fs.appendFile(path, args[i] + "\n", function (err) {
      if (err) {
        console.log("Couldn't append argument to file!");
      }

      else {
        console.log("Argument appended to file!");
      }
    });
  }
}
