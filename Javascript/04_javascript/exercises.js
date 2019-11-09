function keywordusage(string, arr) {
    var splitted = string.split(" ");
    var usage = arr.map(isWordUsed);
    return usage;

    function isWordUsed(word) {
        if (splitted.indexOf(word) !== -1) {
                return true;
        }
        return false;
    }
}


function frequencies(string, words) {
    var splitted = string.split(" ");
    var word_frequencies = {};

    for (var x = 0; x < words.length; x++) {
        word_frequencies[words[x]] = 0;

        for (var y = 0; y < splitted.length; y++) {
            if (words[x] === splitted[y]) {
                word_frequencies[words[x]] += 1;
            }
        }
    }

    return word_frequencies;
}


function rotate(arr, steps) {
    steps = typeof steps !== 'undefined' ? steps : 1;
    var rotated_arr = [];

    if (steps % arr.length == 0) {
        steps = 0;
    }

    else if (steps > arr.length || steps < (arr.length * -1)) {
        steps = steps % arr.length;
    }

    for (var i = 0; i < arr.length; i++) {
        var index = 0;

        if (i + steps < 0) {
            index = i + steps + arr.length;
            rotated_arr.splice(index, 0, arr[i]);
        }

        else if (i + steps < arr.length) {
            index = i + steps;
            rotated_arr.splice(index, 0, arr[i]);
        }

        else if (i + steps >= arr.length) {
            index = (i + steps) - (arr.length);
            rotated_arr.splice(index, 0, arr[i]);
        }
    }
    for (i = 0; i < arr.length; i++) {
        arr[i] = rotated_arr[i];
    }
}
