$(document).ready(function() {

    // Filters questionnaires based on name when user is typing to the search
    $("#searchBox").keyup(function() {
        let val = $.trim(this.value);
        if (val === "") {
            $("[id^=accordion]").show();
        }

        else {
            $("[id^=accordion]").hide();
            $("[id^=accordion]").has(`button:contains(${val})`).show();
        }
    });

    // Gives the delete button the id of the questionnaire
    $(document).on('click', "[id^='deleteBtn']", function(){
        let id = $(this).data('id');
        let type = $(this).data('type');

        $("#modalDeleteBtn").attr("onclick", `window.location.href='/management/delete/id/${id}';`);
        $("#modalTitle").text(`Delete ${type}?`);
    });
});
