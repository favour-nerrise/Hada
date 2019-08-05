window.onload = function(){

( function() {

	// var n=$('.c').attr('id');
    var c = 45;
	$('.c').text(c);
	var timer = setInterval(function(){
		c--;
		if(c >= 0){
			// $('.c').text(c);
      span = document.getElementById("count");
      span.innerHTML = c;
		}
        if(c == 0){
            $('.c').text("Uh-oh!");
            $("#timeout").modal();
        }
	},1000);

  setTimeout(function(){
     timer; //clear above interval after 5 seconds
   },5000);
})();

}

// Start
// c();

// Loop
// setInterval(function(){
// 	c();
// },5000);
