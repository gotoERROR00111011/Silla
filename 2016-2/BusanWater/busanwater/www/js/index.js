var app = {
    initialize: function() {
        this.bindEvents();
    },
    bindEvents: function() {
        document.addEventListener('deviceready', this.onDeviceReady, false);
    },
    onDeviceReady: function() {
        app.receivedEvent('deviceready');
    },
    receivedEvent: function(id) {
    }
};

app.initialize();

$(document).ready(function(){
	//localStorage.setItem("gu", gu);
	//localStorage.removeItem("gu");
	//localStorage.getItem("gu");
	
	var chk1 = localStorage.getItem("yes");
	var chk2 = localStorage.getItem("no");
	if (chk1 == "false") chk1 = null;
	if (chk2 == "false") chk2 = null;
	$("#yes").prop("checked", chk1).checkboxradio("refresh");
	$("#no").prop("checked", chk2).checkboxradio("refresh");
	
	var chk3 = localStorage.getItem("year");
	$("#year").val(chk3).prop("selected", true);
	$("#year").selectmenu('refresh', true);
	
	$('a').click(function(){		
		var url = "water.html?";
		url += "gu=" + this.innerHTML;
		localStorage.setItem("gu", this.innerHTML);
		
		var year = $('#year').val();
		url += "&year=" + year;
		localStorage.setItem("year", year);
		
		var yes = $('#yes').is(':checked');
		var no = $('#no').is(':checked');
		localStorage.setItem("yes", yes);
		localStorage.setItem("no", no);
		
		var water;
		if (yes==1 && no==1){
			water = 0;
		} else if (yes==1 && no==0){
			water = 1;
		} else if (yes==0 && no==1){
			water = 2;
		} else {
			water = 0;
		}
		url += "&water=" + water;
		
		location.replace(url);
	});
});