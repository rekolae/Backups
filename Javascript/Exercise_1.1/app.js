var args = process.argv.slice(2);
var total = 0;

for (var i = 0; i < args.length; i++) {

  // Check if given argument can be turned into a number
  if (!isNaN(Number(args[i]))) {
    total = total + Number(args[i]);
  }
}

console.log(total);
