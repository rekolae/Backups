$(document).ready(function() {

  $("#dateForm").submit(function(event){
    event.preventDefault();

    var dates = $(this).serializeArray();
    var start = dates[0].value;
    var end = dates[1].value;

    $.support.cors = true;
    $.ajax({
      url: "https://bwa-2019-2020.herokuapp.com/v1/trips?startDate=" + start + "&endDate=" + end,
      type: "GET",
      dataType: "json",
      headers: { "X-API-Key": "bwa_2019-2020" },
      success: function (result) {

        if($("tbody").length){
	        $("tbody").remove();
        }

        var table_data = "<tbody>";
        for (var i = 0; i < result.length; i++) {
          table_data += '<tr>';
          table_data += '<td>' + result[i].scooter_id + '</td>';
          table_data += '<td>' + result[i].average_speed + '</td>';
          table_data += '</tr>';
        }

        table_data +='</tbody>';
        document.getElementById('trips').innerHTML = table_data;
      }
    });
  });
});
