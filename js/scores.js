// var execution = 0;
//
// $('#execution').on('click', function() {
//   execution += 13;
// //   $('.exec').text(execution);
// //   var elem = document.getElementById("exe");
// //   elem.style.width = execution + '%';
//   $("#exec")
//       .css("width", execution + "%")
//       .attr("aria-valuenow", execution);
// })

core_values_data = {
  datasets : [ {
    label : "My First Dataset",
    data : [ 10, 20, 30, 40],
    backgroundColor :
        [ "rgb(255, 99, 132)", "rgb(54, 162, 235)", "rgb(255, 205, 86)", "rgb(255, 205, 216)" ]
  } ],

  // These labels appear in the legend and in the tooltips when hovering
  // different arcs
  labels : [ 'Execution', 'Integrity', 'Community', 'Passion' ]
};

var ctx = document.getElementById('myChart');

var chart = new Chart(ctx, {
  // The type of chart we want to create
  type : 'doughnut',

  // The data for our dataset
  data : core_values_data,

  // Configuration options go here
  options : {
    responsive : false
  }
});


hada_values_data = {
  datasets : [ {
    label : "My First Dataset",
    data : [ 10, 20, 30, 40],
    backgroundColor :
        [ "rgb(255, 99, 132)", "rgb(54, 162, 235)", "rgb(255, 205, 86)", "rgb(255, 205, 186)" ]
  } ],

  // These labels appear in the legend and in the tooltips when hovering
  // different arcs
  labels : [ 'Race', 'Gender', 'Disability', 'Sexual Orientation' ]
};
var ctx2 = document.getElementById('myChart2');

var chart2 = new Chart(ctx2, {
  // The type of chart we want to create
  type : 'doughnut',

  // The data for our dataset
  data : hada_values_data,

  // Configuration options go here
  options : {
    responsive : false
  }
});
