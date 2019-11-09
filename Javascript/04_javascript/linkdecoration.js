$("#javascript_start").html("[OK] Started executing the javascript file");
$("#javascript_end").html("[WAITING]...this far we haven't reached the end... Maybe you should check dev tools?");

// ADD YOUR CODE BETWEEN THESE LINES //

$(document).ready(
    (function () {
        $("a").not("[href$='.pdf'], [href$='.html']").addClass("download");
        $("a[href$='.pdf']").addClass("pdf");
    })
);

// ADD YOUR CODE BETWEEN THESE LINES //

$("#javascript_end").html("[OK] The end of your javascript file was reached. (meaning there were no huge errors) Hopefully your code works too! ");
